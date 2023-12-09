project('cs764', 'cpp', default_options : 'cpp_std=c++17')


src= [
  'storage.cpp',
  'Assert.cpp',
  'common.cpp',
  'defs.cpp',
  'Filter.cpp',
  'Iterator.cpp',
  'Scan.cpp',
  'Sort.cpp',
]

lib = static_library('sort764', src)


executable('test_storage', 'test_storage.cpp', link_with: lib)
executable('test_scan', 'Test.cpp', link_with: lib)

