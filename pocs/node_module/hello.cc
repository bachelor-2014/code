#include <node.h>
#include <v8.h>
#include <cv.h>
#include <opencv2/opencv.hpp>

using namespace v8;

Handle<Value> Method(const Arguments& args) {
    HandleScope scope;

    // Handling function arguments
    if (args.Length() < 2) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (!args[0]->IsString()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }

    String::Utf8Value strTemp(args[0]->ToString());
    std::string str = std::string(*strTemp);
    std::cout << str << "\n";

    //Handling callback functions
    Local<Function> cb = Local<Function>::Cast(args[1]);
    const unsigned argc = 1;
    Local<Value> argv[argc] = { Local<Value>::New(String::New("Callback argument")) };
    cb->Call(Context::GetCurrent()->Global(), argc, argv);
    
    // Using OpenCV
    std::cout << "OpenCV version: " << CV_VERSION << "\n";

    cv::Mat image;
    image = cv::imread("flower.jpg");

    cv::namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
    cv::imshow( "Display Image", image );

    cv::waitKey(1000);

    return scope.Close(String::New("Success"));
}

Handle<Value> Method2(const Arguments& args) {
    HandleScope scope;
    return scope.Close(String::New("Other function"));
}

void init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("hello"), FunctionTemplate::New(Method)->GetFunction());
    exports->Set(String::NewSymbol("other"), FunctionTemplate::New(Method2)->GetFunction());
}

NODE_MODULE(hello, init)
