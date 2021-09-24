// Stub for building without the real libisolate, which is in src/lib.rs

pub fn isolate<A, B>(fun: impl Fn(A) -> B, arg: A) -> B {
	fun(arg)
}
