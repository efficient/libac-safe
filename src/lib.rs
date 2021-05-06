use gotcha::Group;
use gotcha::group_thread_set;

pub fn isolate<A, B>(fun: impl Fn(A) -> B, arg: A) -> B {
	thread_local! {
		static GROUP: Isolate = Isolate::default();
	}
	GROUP.with(|group| isolate_r(fun, arg, *group))
}

pub fn isolate_r<A, B>(fun: impl Fn(A) -> B, arg: A, ctx: Isolate) -> B {
	let Isolate (group) = ctx;
	group_thread_set!(group);

	let res = fun(arg);

	group_thread_set!(Group::SHARED);
	res
}

#[derive(Clone)]
#[derive(Copy)]
pub struct Isolate (Group);

impl Default for Isolate {
	fn default() -> Self {
		Self (Group::new().expect("Ran out of libsets!"))
	}
}
