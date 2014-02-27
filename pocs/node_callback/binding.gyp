{
  'variables': {
      'node_texample_sources': [
          "texample.cpp"
      ],
      'node_root': '../node-0.7.0',
      'node_root_win': 'c:\\node',  # fill in with Windows info if needed
      'deps_root_win': 'c:\\dev2',
      'target_arch' : 'x64'  # needed b/c we are on a 64-bit Linux
  },
  'targets': [
    {
      'target_name': 'texample',
      'product_name': 'texample',
      'type': 'loadable_module',
      'product_prefix': '',
      'product_extension':'node',
      'sources': [
        '<@(node_texample_sources)'
      ],
      'defines': [
        'PLATFORM="<(OS)"',
        '_FILE_OFFSET_BITS=64'
      ],
      'conditions': [
        [ 'OS=="linux"', {
        'cflags': ['-fPIC'],  # needed on 64-bit linux, for the .node SO to work
          'libraries': [
           "-lev" 
          ],
          'include_dirs': [
             'src/',
             '<@(node_root)/include/node',
             '<@(node_root)/include',
             '<@(node_root)/deps/uv/include/uv-private',
             '../expanded-prereqs/include'
          ],
          'defines': [
            #'HAVE_CAIRO',
            '_LARGEFILE_SOURCE'
          ],
        }],
        [ 'OS=="win"', {
          'defines': [
            'HAVE_CAIRO',
            'PLATFORM="win32"',
            '_LARGEFILE_SOURCE',
            '_FILE_OFFSET_BITS=64',
            '_WINDOWS',
            '__WINDOWS__', # ltdl
            'BUILDING_NODE_EXTENSION'
          ],
          'libraries': [ 
              'mapnik2.lib',
              'node.lib',
              'icuuc.lib',
              'libboost_regex-vc100-mt-1_48.lib',
          ],
          'include_dirs': [
             'c:\\mapnik-2.0\\include',
             '<@(node_root_win)\\src',
             '<@(node_root_win)\\deps\\uv\\include\\private',
          ],
          'msvs_settings': {
            'VCLinkerTool': {
              'AdditionalLibraryDirectories': [
                '<@(node_root_win)\\Release\\lib',
                '<@(node_root_win)\\Release',
                '<@(deps_root_win)\\mapnik-packaging\\windows\\build\\src\\msvc-9.0\\release\\threading-multi',
                '<@(deps_root_win)\\boost-vc100\\lib',
                '<@(deps_root_win)\\icu\\lib',
              ],
            },
          },
        },
      ],
      ]
    },
  ],
}
