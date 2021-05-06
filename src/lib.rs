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
		use gotcha::group_lookup_symbol_fn;
		let group = Group::new().expect("Ran out of libsets!");
		let swallow_panics: fn() = unsafe {
			group_lookup_symbol_fn!(group, swallow_panics)
		}.unwrap();
		swallow_panics();
		Self (group)
	}
}

#[no_mangle]
fn swallow_panics() {
	use std::panic::set_hook;
	set_hook(Box::new(|_| ()));
}
