#ifndef SPECTRUM
#define SPECTRUM

#define NB_DATA	128
#define MAX_VAL	65535
#define NB_CHANNELS	3
#define BAR_SPACING	1

class spectrum {

	public:

		int startX;
		int startY;
		int totalWidth;
		int totalHeight;
		int barWidth;

		ofColor colBG;
		int tintBars;

		string serialMsg;
		vector<int> freqs;

		Spectrum(int _x, int _y, int _tx, int _ty, int _w, ofColor _colBG, int _colBar);
		void addData(int val);
		void drawGraph();
};

#endif
