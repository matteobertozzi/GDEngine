#!/usr/bin/env python
#-*- coding: utf-8 -*-

import commands
import string
import sys
import os

def execCommand(cmd):
    return commands.getstatusoutput(cmd)

def writeFile(filename, content):
    fd = open(filename, 'w')
    fd.write(content)
    fd.close()

def platformIsMac():
    return os.uname()[0] == 'Darwin'

def platformIsLinux():
    return os.uname()[0] == 'Linux'

class Build:
    def __init__(self, cflags=None, defines=None, includes=None, ldlibs=None):
        # Compiler
        self.cc = self._findCompiler()

        # Setup Temp Directories
        self.dir_obj = '.BUILD-OBJ'
        self.dir_out = 'BUILD-OUT'

        # CFlags
        self.cflags = self._defaultCFlags()
        if not cflags is None:
            self.cflags.extend(cflags)

        # Defines
        self.defines = self._defaultDefines()
        if not defines is None:
            self.defines.extend(defines)

        # Include Paths
        self.includes = self._defaultIncludes()
        if not includes is None:
            self.includes.extend(includes)

        # LD Libs
        self.ldlibs = self._defaultLdLibs()
        if not ldlibs is None:
            self.ldlibs.extend(ldlibs)

    def addCFlags(self, cflags):
        self.cflags.extend(cflags)

    def addDefines(self, defines):
        self.defines.extend(defines)

    def addIncludePaths(self, includes):
        self.includes.extend(includes)

    def addLdLibs(self, ldlibs):
        self.ldlibs.extend(ldlibs)

    def setDirObj(self, dir_path):
        self.dir_obj = dir_path
        if not os.path.exists(self.dir_obj):
            os.makedirs(self.dir_obj)

    def setDirOutput(self, dir_path):
        self.dir_out = dir_path
        if not os.path.exists(self.dir_out):
            os.makedirs(self.dir_out)

    def cleanup(self):
        self._removeDirectory(self.dir_obj)

    def buildApp(self, app_name, dirs_src):
        print 'Building %s' % (app_name)
        print '-' * 60

        for dir_src in dirs_src:
            self.compileDirectory(dir_src)

        obj_list = os.listdir(self.dir_obj)
        obj_list = [os.path.join(self.dir_obj, f) for f in obj_list]

        app_path = os.path.join(self.dir_out, app_name)

        cmd = '%s -o %s %s %s' %                   \
                (self.cc, app_path,                \
                 string.join(obj_list, ' '),       \
                 string.join(self.ldlibs, ' '))

        print ' [LD]', app_name
        exit_code, output = execCommand(cmd)
        if exit_code != 0:
            print ' * Failed with Status', exit_code
            print ' *', cmd
            print output
            sys.exit(1)
        print

    def buildLibrary(self, libname, libversion, dirs_src):
        print 'Building %s %s Library' % (libname, libversion)
        print '-' * 60

        for dir_src in dirs_src:
            self.compileDirectory(dir_src)

        obj_list = os.listdir(self.dir_obj)
        obj_list = [os.path.join(self.dir_obj, f) for f in obj_list]

        libversion_maj = libversion[:libversion.index('.')]
        lib_ext = 'dlib' if platformIsMac() else 'so'
        lib_name = 'lib%s.%s' % (libname, lib_ext)
        lib_name_maj = 'lib%s.%s.%s' % (libname, lib_ext, libversion_maj)
        lib_name_full = 'lib%s.%s.%s' % (libname, lib_ext, libversion)
        lib_path = os.path.join(self.dir_out, lib_name_full)

        if platformIsMac():
            cmd = '%s -o %s -dynamiclib %s %s' % \
		            (self.cc, lib_path,       \
        	         string.join(obj_list, ' '),            \
            	     string.join(self.ldlibs, ' '))
        elif platformIsLinux():
	        cmd = '%s -shared -Wl,-soname,%s -o %s %s %s' % \
    	            (self.cc, lib_name_maj, lib_path,           \
        	         string.join(obj_list, ' '),            \
            	     string.join(self.ldlibs, ' '))

        print
        print ' [LD]', lib_name_full
        exit_code, output = execCommand(cmd)
        if exit_code != 0:
            print ' * Failed with Status', exit_code
            print ' *', cmd
            print output
            sys.exit(1)

        cwd = os.getcwd()
        os.chdir(self.dir_out)
        for name in (lib_name, lib_name_maj):
            print ' [LN]', name
            execCommand('ln -s %s %s' % (lib_name_full, name))
        os.chdir(cwd)

        print

    def buildMiniTools(self, name, dir_src):
        print 'Building %s' % (name)
        print '-' * 60

        self.compileDirectory(dir_src)

        for obj_name in os.listdir(self.dir_obj):
            app_name = obj_name[:-2]
            app_path = os.path.join(self.dir_out, app_name)
            obj_path = os.path.join(self.dir_obj, obj_name)

            cmd = '%s -o %s %s %s' %                   \
                    (self.cc, app_path, obj_path,      \
                     string.join(self.ldlibs, ' '))
            print ' [LD]', app_name
            exit_code, output = execCommand(cmd)
            if exit_code != 0:
                print ' * Failed with Status', exit_code
                print ' *', cmd
                print output
                sys.exit(1)
        print

    def compileDirectory(self, dir_src):
        for root, dirs, files in os.walk(dir_src, topdown=False):
            for name in files:
                if name.endswith('.c'):
                    self.compileFile(os.path.join(root, name))

    def compileFile(self, filename):
        objfile = os.path.basename(filename)
        objfile = objfile[:objfile.rindex('.')] + '.o'
        objfile = os.path.join(self.dir_obj, objfile)

        cmd = '%s -c %s %s %s %s -o %s' %         \
               (self.cc,                          \
                string.join(self.cflags, ' '),    \
                string.join(self.defines, ' '),   \
                string.join(self.includes, ' '),  \
                filename,
                objfile)

        print ' [CC]', filename
        exit_code, output = execCommand(cmd)
        if exit_code != 0:
            print ' * Failed with Status', exit_code
            print ' * %s' % (cmd)
            print output
            sys.exit(1)

    def _removeFile(self, path):
        if os.path.exists(path):
            os.remove(path)

    def _removeDirectory(self, path):
        if os.path.exists(path):
            for root, dirs, files in os.walk(path, topdown=False):
                for name in files:
                    os.remove(os.path.join(root, name))
            os.removedirs(path)

    def _findCompiler(self):
        return('/usr/bin/gcc')

    def _defaultCFlags(self):
        return ['-g', '-O3', '-Wall', '-fno-strict-aliasing', '-Werror']

    def _defaultDefines(self):
        return ['-D__USE_FILE_OFFSET64']

    def _defaultIncludes(self):
        return []

    def _defaultLdLibs(self):
        return ['-lm']

class GDEngineBuild:
    def __init__(self):
        self.lib_version_code = 0x100000
        self.lib_version = '1.0.0'
        self.lib_name = 'gdengine'
        self.lib_hname = 'GDEngine'

        self.build_name = '1A'
        self.build_version = 0
        if os.path.exists('.build_version'):
            fd = open('.build_version')
            self.build_version = int(fd.read().strip()) + 1
            fd.close()

        # Write Build Version File
        fd = open('.build_version', 'w')
        fd.write('%d' % self.build_version)
        fd.close()

        self.build_name += '%05d' % self.build_version

        self.dir_obj = './.BUILD-LIB-OBJ'
        self.dir_out = '.'

        print 'Build %s %s' % (self.lib_hname, self.build_name)
        Build()._removeDirectory(self.dir_obj)
        self._setupLibs()
        self._generatePubHeaders()

    def _setupLibs(self):
        # SUPPORTS
        self.support_opengl = True
        self.support_png = True
        self.support_jpg = False
        # -----------------------------------------------------------------

        self.app_includes = ['-I./']
        if platformIsMac():
            self.app_ldlibs = ['%s.dlib' % os.path.join(self.dir_out, 'lib' + self.lib_name),
                               '-framework GLUT', '-framework OpenGL']
        else:
            self.app_ldlibs = ['-L%s -l%s' % (self.dir_out, self.lib_name), 
                               '-lglut', '-lGL', '-lGLU']

        self.lib_src_dirs = ['engine']
        self.lib_includes = ['-I./', 
                             '-I./engine/core',
                             '-I./engine/images',
                             '-I./engine/math', 
                             '-I./engine/models', 
                             '-I./engine/physics']
        self.lib_cflags = ['-fPIC']
        self.lib_ldlibs = []

        if platformIsMac():
            self.lib_ldlibs.extend(['-framework GLUT', '-framework OpenGL'])

        # Extra Include/Libs
        if self.support_png:
            _, pngInclude = execCommand('libpng12-config --cflags')
            _, pngLib = execCommand('libpng12-config --libs')
            self.lib_ldlibs.extend([pngLib, '-L/usr/X11/lib'])
            self.lib_includes.append(pngInclude)

            self.app_ldlibs.extend([pngLib, '-L/usr/X11/lib'])
            self.app_includes.append(pngInclude)

        if self.support_opengl:
            self.lib_src_dirs.append('opengl')
            self.lib_includes.append('-I./engine/opengl')

    def _generatePubHeaders(self):
        dir_pubhead = './GDEngine'       
        dirs_src = self.lib_src_dirs

        if os.path.exists(dir_pubhead):
            Build()._removeDirectory(dir_pubhead)
        os.makedirs(dir_pubhead)

        replaceNames = {    'imagereader.h':'ImageReader.h',
                            'imagepool.h':'ImagePool.h',
                            'mipmap.h':'MipMap.h',
                            'modelreader.h':'ModelReader.h',
                            'modelmesh.h':'ModelMesh.h',
                            'modelbone.h':'ModelBone.h',
                            'vertexbone.h':'VertexBone.h',
                            'opengl.h':'OpenGL.h',
                       }

        for dir_src in dirs_src:
            for root, dirs, files in os.walk(dir_src, topdown=False):
                if root.endswith('private'):
                    continue

                for name in files:
                    if name.endswith('.h'):
                        in_path = os.path.join(root, name)
                        
                        if name in replaceNames:
                            out_name = replaceNames[name]
                        else:
                            out_name = name[0].upper() + name[1:]

                        out_path = os.path.join(dir_pubhead, out_name)
                        cmd = 'cp %s %s' % (in_path, out_path)
                        exit_code, output = execCommand(cmd)

        # Generate Config File
        config_source  = '#ifndef _GD_ENGINE_CONFIG_H_\n'
        config_source += '#define _GD_ENGINE_CONFIG_H_\n'
        config_source += '\n'
        config_source += '#define GD_ENGINE_BUILD_NAME     "%s"\n' % (self.build_name)
        config_source += '#define GD_ENGINE_VERSION        "%s"\n' % (self.lib_version)
        config_source += '#define GD_ENGINE_VERSION_CODE   0x%x\n' % (self.lib_version_code)
        config_source += '\n'
        if self.support_opengl: config_source += '#define GD_ENGINE_OPENGL_SUPPORT\n'
        config_source += '\n'
        if self.support_png: config_source += '#define GD_ENGINE_PNG_SUPPORT\n'
        if self.support_jpg: config_source += '#define GD_ENGINE_JPG_SUPPORT\n'
        config_source += '\n'
        config_source += '#endif /* !_GD_ENGINE_CONFIG_H_ */\n'
        writeFile(os.path.join(dir_pubhead, 'Config.h'), config_source)

    def buildLibrary(self):
        dirs_src = self.lib_src_dirs
        cflags = self.lib_cflags
        cflags_version = [ '-D _GD_ENGINE_BUILD_NAME=%s' % (self.build_name),
                           '-D _GD_ENGINE_VERSION=%s' % (self.lib_version) ]

        build = Build()
        build.setDirObj(self.dir_obj)
        build.setDirOutput(self.dir_out)
        build.addLdLibs(self.lib_ldlibs)
        build.addCFlags(cflags)
        build.addCFlags(cflags_version)
        build.addIncludePaths(self.lib_includes)
        build.buildLibrary(self.lib_name, self.lib_version, dirs_src)
        build.cleanup()

    def buildUnitTests(self):        
        dir_unit_tests = 'unit-tests'
        dir_unit_tests_src = os.path.join(dir_unit_tests, 'src')

        functions = []
        for root, dirs, files in os.walk(dir_unit_tests_src, topdown=False):
            for name in files:
                functions.append(name[:-2])

        # Setup Func Source
        func_source  = '#include "unittest.h"\n'
        func_source += '\n'
        for func in functions:
            func_source += 'extern void %s (GDUnitTests *unitTests);\n' % (func)
        func_source += '\n'
        func_source += 'GDUnitTestFunc unitTestFuncs[] = {\n'
        for func in functions:
            func_source += '     %s,\n' % (func)
            func_source += '     NULL\n'
        func_source += '};\n'

        # Write Test Func Source
        writeFile(os.path.join(dir_unit_tests, 'tests.c'), func_source)

        # Build Unit Tests
        build = Build()
        build.setDirObj(self.dir_obj)
        build.setDirOutput(self.dir_out)
        build.addLdLibs(self.app_ldlibs)
        build.addIncludePaths(self.app_includes)
        build.addIncludePaths(['-I./%s' % (dir_unit_tests)])
        build.buildApp('unit-tests-library', [dir_unit_tests])
        build.cleanup()

    def executeUnitTests(self):
        print ' [T] GLData Tests'
        cmd = 'LD_LIBRARY_PATH=%s %s' %     \
                (self.dir_out, os.path.join(self.dir_out, 'unit-tests-library'))
        print cmd
        exit_code, output = execCommand(cmd)
        if exit_code != 0:
            print ' * Failed with Status', exit_code
            print ' * ', cmd
            sys.exit(exit_code)
        print output

    def buildExamples(self):
        dir_src = './examples/'

        build = Build()
        build.setDirObj(self.dir_obj)
        build.setDirOutput(self.dir_out)
        build.addLdLibs(self.app_ldlibs)
        build.addIncludePaths(self.app_includes)
        build.buildMiniTools('Examples', dir_src)
        build.cleanup()

    def executeExample(self, name):
        print ' [T] GLData Tests'
        cmd = 'LD_LIBRARY_PATH=%s %s' %     \
                (self.dir_out, os.path.join(self.dir_out, name))
        print cmd
        exit_code, output = execCommand(cmd)
        if exit_code != 0:
            print ' * Failed with Status', exit_code
            print ' * ', cmd
            sys.exit(exit_code)
        print output

def main(argv):
    gdBuild = GDEngineBuild()
    gdBuild.buildLibrary()
    gdBuild.buildUnitTests()
    gdBuild.executeUnitTests()

    gdBuild.buildExamples()
    #gdBuild.executeExample('test')

if __name__ == '__main__':
    main(sys.argv)

