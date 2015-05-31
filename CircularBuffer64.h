/** Circular buffer object.  Has a fixed number of cells, set to 64.
@tparam ITEM_TYPE the kind of data to store, eg. int, int8_t etc.
*/
template <class ITEM_TYPE>
class CircularBuffer64
{

public:
	/** Constructor
	*/
	CircularBuffer64(): start(0),end(0),s_msb(0),e_msb(0)
	{
	}

	inline
	bool isFull() {
		return end == start && e_msb != s_msb;
	}

	inline
	bool isEmpty() {
		return end == start && e_msb == s_msb;
	}

	inline
	void write(ITEM_TYPE in) {
		items[end] = in;
		//if (isFull()) cbIncrStart(); /* full, overwrite moves start pointer */
		cbIncrEnd();
	}

	inline
	ITEM_TYPE read() {
		ITEM_TYPE out = items[start];
		cbIncrStart();
		return out;
	}

	inline
	unsigned long count() {
		return (num_buffers_read << 8) + start;
	}

private:
	ITEM_TYPE items[64];
	uint8_t         start;  /* index of oldest itement              */
	uint8_t         end;    /* index at which to write new itement  */
	uint8_t         s_msb;
	uint8_t         e_msb;
	unsigned long num_buffers_read;


	inline
	void cbIncrStart() {
		start++;
		if (start%64 == 0) {
		  start = 0;
			s_msb ^= 1;
			num_buffers_read++;
		}
	}

	inline
	void cbIncrEnd() {
		end++;
		if (end%64 == 0){
		  end = 0;
		  e_msb ^= 1;
		}
	}

};