# File read sample

Shows how to read a file.

The sample shows two modes: with and without a callback function.

## Details

The sample class is [GameModule](Source/Game.cppm).

First of all, you need to get the interface `PonyEngine::File::IFileService`.

Then you need to open a file by path. You also need to provide file parameters.
It's a group of different settings. But it has default ones. 
And in sample one of them is used - `PonyEngine::File::FileParams::Read()` which returns default parameters for file read opetations.
The file is closed automatically when its handle goes out of scope.

After that the file is ready for read operations. Call `PonyEngine::File::IFile::Read()` to submit a read operation.
The function takes two arguments: `PonyEngine::File::ReadParams` and a callback `std::move_only_function<void(const PonyEngine::File::IReadRequest&) noexcept> callback`.
The read parameters tell where to store read bytes and at what offset to read the file.
The callback is optional. If it's set, it will be called on the operation finish. Be careful, as the callback is executed on an IO thread.
It also means that you mustn't do expensive operations in the callback and must return as quickly as possible.
A request can be waited via `Wait()` function on a request.
You can cancel a request as well via calling `Cancel()` on a request. But it only submits a cancel request, it doesn't guarantee that the request will really be canceled.
It still may finish with a success or failure.

In any case, till a request is finished, you must keep a file object, a request object, a target buffer and a callback (if it was set) alive.
