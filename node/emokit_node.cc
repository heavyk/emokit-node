
#include <node.h>
#include <v8.h>
#include "emokit/emokit.h"

using namespace v8;

emokit_device* d;

//TODO: make this an object
Handle<Value> MyFunction(const Arguments& args) {
	HandleScope scope;
	if(emokit_read_data(d) >= 0) {
		emokit_get_next_frame(d);
		
		Local<Object> obj = Object::New();
		obj->Set(String::NewSymbol("battery"), Number::New(d->current_frame.battery));
		obj->Set(String::NewSymbol("gyroX"), Number::New(d->current_frame.gyroX));
		obj->Set(String::NewSymbol("gyroY"), Number::New(d->current_frame.gyroY));
		obj->Set(String::NewSymbol("F3"), Number::New(d->current_frame.F3));
		obj->Set(String::NewSymbol("FC6"), Number::New(d->current_frame.FC6));
		obj->Set(String::NewSymbol("P7"), Number::New(d->current_frame.P7));
		obj->Set(String::NewSymbol("T8"), Number::New(d->current_frame.T8));
		obj->Set(String::NewSymbol("F7"), Number::New(d->current_frame.F7));
		obj->Set(String::NewSymbol("F8"), Number::New(d->current_frame.F8));
		obj->Set(String::NewSymbol("T7"), Number::New(d->current_frame.T7));
		obj->Set(String::NewSymbol("P8"), Number::New(d->current_frame.P8));
		obj->Set(String::NewSymbol("AF4"), Number::New(d->current_frame.AF4));
		obj->Set(String::NewSymbol("F4"), Number::New(d->current_frame.F4));
		obj->Set(String::NewSymbol("AF3"), Number::New(d->current_frame.AF3));
		obj->Set(String::NewSymbol("O2"), Number::New(d->current_frame.O2));
		obj->Set(String::NewSymbol("O1"), Number::New(d->current_frame.O1));
		obj->Set(String::NewSymbol("FC5"), Number::New(d->current_frame.FC5));

		return scope.Close(obj);
	} else {
		return scope.Close(False());
	}
}

Handle<Value> Init(const Arguments& args) {
	HandleScope scope;
	if(d != NULL) emokit_delete(d);
	d = emokit_create();
	return scope.Close(Number::New(emokit_get_count(d, EMOKIT_VID, EMOKIT_PID)));
}

Handle<Value> Connect(const Arguments& args) {
	HandleScope scope;
	if(emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0) == 0) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(MyFunction);
		Local<Function> fn = tpl->GetFunction();
		fn->SetName(String::NewSymbol("read_data"));
		return scope.Close(fn);
	} else {
		return scope.Close(False());
	}
}

Handle<Value> Close(const Arguments& args) {
	HandleScope scope;
	emokit_close(d);
	emokit_delete(d);
	return scope.Close(Undefined());
}

/*
Handle<Value> Add(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 2) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}

	if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

	Local<Number> num = Number::New(args[0]->NumberValue() +
			args[1]->NumberValue());
	return scope.Close(num);
}
*/



void init(Handle<Object> target) {
	target->Set(String::NewSymbol("init"), FunctionTemplate::New(Init)->GetFunction());
	target->Set(String::NewSymbol("connect"), FunctionTemplate::New(Connect)->GetFunction());
	target->Set(String::NewSymbol("close"), FunctionTemplate::New(Close)->GetFunction());
}
NODE_MODULE(emokit, init)
