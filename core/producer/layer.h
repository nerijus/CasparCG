#pragma once

#include <common/memory/safe_ptr.h>
#include <common/utility/printable.h>

#include <boost/noncopyable.hpp>

#include <tbb/atomic.h>

#include <memory>

namespace caspar { namespace core {

class frame_producer;
class draw_frame;

class layer : boost::noncopyable
{
public:
	layer(int index, const printer& parent_printer = nullptr); // nothrow
	~layer();
	layer(layer&& other); // nothrow
	layer& operator=(layer&& other); // nothrow

	// Swap is thread-safe on "other".
	void swap(layer& other); // nothrow 
		
	void load(const safe_ptr<frame_producer>& producer, bool play_on_load = false); // nothrow
	void preview(const safe_ptr<frame_producer>& producer); // nothrow
	void play(); // nothrow
	void pause(); // nothrow
	void stop(); // nothrow
	void clear(); // nothrow

	safe_ptr<frame_producer> foreground() const; // nothrow
	safe_ptr<frame_producer> background() const; // nothrow

	safe_ptr<draw_frame> receive(); // nothrow

	std::wstring print() const;
private:
	struct implementation;
	tbb::atomic<implementation*> impl_;
};

}}