{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "splotbot_wrapper.cc","../cpp/splotbot.cpp" ],
      "libraries": [
        "<!@(pkg-config --libs --cflags opencv)",
      ],
      "conditions": [
        ['OS=="mac"', {
            # cflags on OS X are stupid and have to be defined like this
            'xcode_settings': {
                'OTHER_CFLAGS': [
                    "-mmacosx-version-min=10.7",
                    "-std=c++11",
                    "-stdlib=libc++",
                    '<!@(pkg-config --cflags opencv)'
                ],
                "GCC_ENABLE_CPP_RTTI": "YES",
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
            }
        }] 
      ]
    }

  ]
}
