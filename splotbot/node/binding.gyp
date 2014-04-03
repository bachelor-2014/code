{
  "targets": [
    {
      "target_name": "addon",
      "sources":
      ["addon.cc","splotbot_wrapper.cc",
"../cpp/libraries/cJSON/cJSON.cpp","../cpp/utils/base64.cpp","../cpp/utils/threading.cpp","../cpp/component.cpp","../cpp/mendel.cpp",
"../cpp/instructionbuffer.cpp","../cpp/camera.cpp","../cpp/singlesteppermotor.cpp","../cpp/rcservomotor.cpp","../cpp/xyaxes.cpp",
"../cpp/componentinitializer.cpp","../cpp/splotbot.cpp","../cpp/logging/logger.cpp",
"../cpp/logging/filelogger.cpp","../cpp/logging/videologger.cpp"],
      "libraries": [
        "<!@(pkg-config --libs --cflags opencv)",
      ],
      "ldflags":[
        "-lm", "-pthread", "-ggdb", "-lcurl"
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      "defines": [ "DEBUG", "_DEBUG" ]
    }
  ]
}
