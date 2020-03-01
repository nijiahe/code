#pragma once

template<class BinNode>

class ExtremumGetter
{
public:
	ExtremumGetter(BinNode *min = 0, BinNode *max = 0) {
		init(min, max);
	}

	void operator() (BinNode *p) {
		if ((min_ && p->pos < min_->pos) || !min_) { min_ = p; }
		if ((max_ && p->pos > max_->pos) || !max_) { max_ = p; }
	}

	void init(BinNode *min, BinNode *max) {
		min_ = min; max_ = max;
		if (min_ && max_ && max_->pos < min_->pos) {
			std::swap(min_, max_);
		}
	}
	BinNode *min() const { return min_; }
	BinNode *max() const { return max_; }
private:
	BinNode *min_;
	BinNode *max_;
};
