#include "guarded.h"

#include <deque>
#include <list>
#include <map>
#include <memory>
#include <unordered_map>
#include <variant>
#include <vector>

using std::monostate;

struct cexample {
	static bool realm() {
		using std::deque;
		using std::list;
		using std::map;
		using std::move;
		using std::shared_ptr;
		using std::unique_ptr;
		using std::unordered_map;
		using std::vector;
		auto res = false;

		unique_ptr<Guarded<bool>> unique(new Guarded<bool>("unique_ptr"));
		res = res || unique;

		shared_ptr<Guarded<bool>> shared(new Guarded<bool>("shared_ptr"));
		res = res || shared;

		vector<Guarded<bool>> vec(1, "vector");
		res = res || vec[0];

		deque<Guarded<bool>> deq(1, "deque");
		res = res || deq[0];

		list<Guarded<bool>> linked(1, "list");
		res = res || linked.front();

		unordered_map<monostate, Guarded<bool>> hash({{monostate(), "unordered_map"}});
		res = res || hash.at(monostate());

		map<monostate, Guarded<bool>> btree({{monostate(), "map"}});
		res = res | btree.at(monostate());

		return res;
	}
};

static void panic() {
	throw monostate();
}

int main() {
	cexample::realm();
	try {
		panic();
	} catch(monostate) {}
}

template<> bool default_val() {
	return false;
}
