from distutils.core import setup, Extension

utils_ext = Extension('utils', 
                      sources=['utilsmodule.cpp'],
                      extra_compile_args=['-std=c++11'])

setup(name='utils',
      ext_modules=[utils_ext],
      )
