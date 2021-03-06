{
  "targets": [
    {
      "target_name": "addon",
      "sources":
      ["addon.cc","splotbot_wrapper.cc",
"../cpp/libraries/cJSON/cJSON.cpp","../cpp/utils/base64.cpp",
"../cpp/utils/threading.cpp","../cpp/computer_vision/imagestitcher.cpp",
"../cpp/computer_vision/featuresimagestitcher.cpp",
"../cpp/computer_vision/positionimagestitcher.cpp",
"../cpp/computer_vision/featuresandpositionimagestitcher.cpp",
"../cpp/computer_vision/calibrator.cpp",
"../cpp/scanner.cpp",
"../cpp/cameracalibrator.cpp",
"../cpp/component.cpp","../cpp/mendel.cpp",
"../cpp/instructionbuffer.cpp","../cpp/camera.cpp",
"../cpp/singlesteppermotor.cpp","../cpp/rcservomotor.cpp",
"../cpp/xyaxes.cpp","../cpp/scanner.cpp",
"../cpp/componentinitializer.cpp","../cpp/splotbot.cpp",
"../cpp/logging/logger.cpp","../cpp/logging/filelogger.cpp",
"../cpp/logging/videologger.cpp",
"../cpp/logging/imagelogger.cpp",
"../cpp/computer_vision/dropletdetector.cpp",
"../cpp/computer_vision/computervisionutils.cpp",
"../cpp/utils/errors.cpp",
"../cpp/rucolang/Absyn.cpp",
"../cpp/rucolang/rucola.tab.cpp",
"../cpp/rucolang/lex.yy.cpp",
"../cpp/rucolang/rucola.cpp"
],
      "libraries": [
        "<!@(pkg-config --libs --cflags opencv cvblob)",
      ],
      "ldflags":[
         "-lfl","-lm", "-pthread", "-ggdb", "-lcurl"
      ],
      'link_settings': {
          'libraries': [
              '-lfl',
	      '-lcurl'
          ]
      },
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions','-fno-rtti'],
      "defines": [ "DEBUG", "_DEBUG" ]
    }
  ]
}
