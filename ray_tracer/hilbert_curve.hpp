#ifndef __HILBERT_CURVE_HPP__
#define __HILBERT_CURVE_HPP__

namespace ray_tracer {

	class hilbert_curve {

	public:
		void init(int);
		bool next(int &, int &);
		bool eof() const;
	private:
		typedef std::vector<std::pair<int, int> > point_container_t;
		typedef std::pair<int, int> point_t;

		point_container_t aftrans(int, int, point_container_t, int, int);
		point_container_t hilbert(int);

	private:
		point_container_t curve;
		int iter;
	};
}

#endif
