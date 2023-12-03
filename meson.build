project('cs764', 'cpp', default_options : 'cpp_std=c++17')


src= [
  'storage.cpp'
]

lib = static_library('sort', src)


executable('test_storage', 'test_storage.cpp', link_with: lib)


