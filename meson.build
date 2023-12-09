project('cs764', 'cpp', default_options : 'cpp_std=c++17')


src= [
  'storage.cpp',
  'Assert.cpp',
  'common.cpp',
  'defs.cpp',
  'Iterator.cpp',
  'Scan.cpp',
  'InSort.cpp',
  'eSort.cpp',
  'Queue.cpp',
  'Tournament.cpp'
]

lib = static_library('sort764', src)


executable('test_storage', 'test_storage.cpp', link_with: lib)
executable('test_scan', 'Test.cpp', link_with: lib)
executable('test_tournament', 'storage.cpp', 'common.cpp', 'defs.cpp', 'Iterator.cpp', 'Queue.cpp', 'Tournament.cpp', 'TournamentTester.cpp', link_with: lib)

