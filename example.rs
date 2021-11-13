#[cfg(feature = "isolate")]
extern crate isolate;
mod guarded;
#[cfg(not(feature = "isolate"))]
mod isolate;

fn main() {
	use isolate::isolate;
	use std::panic::catch_unwind;
	isolate(realm, ());
	assert!(isolate(catch_unwind, panic).is_err());
}

#[inline(never)]
fn realm(_: ()) -> bool {
	use guarded::Bool;
	use std::borrow::Cow;
	use std::collections::BinaryHeap;
	use std::collections::BTreeMap;
	use std::collections::HashMap;
	use std::collections::LinkedList;
	use std::collections::VecDeque;
	use std::iter;
	use std::rc::Rc;
	use std::sync::Arc;
	let mut res = false;

	let mem = Box::from(Bool::tagged("Box"));
	res = res || **mem;

	let mem = Rc::from(Bool::tagged("Rc"));
	res = res || **mem;

	let mem = Arc::from(Bool::tagged("Arc"));
	res = res || **mem;

	let mem = Bool::tagged("Cow");
	let mut mem = Cow::Borrowed(&mem);
	res = res || **mem;

	let coll = vec![Bool::tagged("Vec")];
	res = res || *coll[0];

	let coll: VecDeque<_> = iter::once(Bool::tagged("VecDeque")).collect();
	res = res || *coll[0];

	let coll: LinkedList<_> = iter::once(Bool::tagged("LinkedList")).collect();
	res = res || **coll.front().unwrap();

	let coll: BinaryHeap<_> = iter::once(Bool::tagged("BinaryHeap")).collect();
	res = res || **coll.peek().unwrap();

	let coll: HashMap<_, _> = iter::once(((), Bool::tagged("HashMap"))).collect();
	res = res || *coll[&()];

	let coll: BTreeMap<_, _> = iter::once(((), Bool::tagged("BTreeMap"))).collect();
	res = res || *coll[&()];

	**mem.to_mut() = true;
	res = res || **mem;

	res
}

#[inline(never)]
#[no_mangle]
fn panic() {
	panic!();
}
