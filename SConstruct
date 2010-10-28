# -*-Python-*-
Library('asmjit', Glob('AsmJit/*.cpp'))
Program('test', ['kmp.c', 'test.c'])
Program('asj', ['asj.cc'], LIBS='asmjit', LIBPATH='.')
