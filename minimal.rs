mod guarded;

fn main() {
	use std::panic::catch_unwind;

	assert!(realm());
	assert!(catch_unwind(panic).is_err());
}

#[inline(never)]
fn realm() -> bool {
	use guarded::Bool;

	*Bool::tagged("Bool")
}

#[inline(never)]
#[no_mangle]
fn panic() {
	panic!();
}
