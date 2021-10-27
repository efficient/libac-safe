use std::cmp::Ordering;
use std::ops::Deref;
use std::ops::DerefMut;

pub type Bool = Guarded<bool>;

pub struct Guarded<T> {
	_tag: Guard,
	val: T,
}

impl<T: Default> Guarded<T> {
	pub fn tagged(tag: &'static str) -> Self {
		Self::tagged_val(tag, T::default())
	}
}

impl<T> Guarded<T> {
	pub fn tagged_val(tag: &'static str, val: T) -> Self {
		let tag = Guard (tag);
		tag.new();
		Self {
			_tag: tag,
			val,
		}
	}
}

impl<R: ?Sized, T: AsRef<R>> AsRef<R> for Guarded<T> {
	fn as_ref(&self) -> &R {
		self.val.as_ref()
	}
}

impl<T: Clone> Clone for Guarded<T> {
	fn clone(&self) -> Self {
		println!("tagged(<cloned>)");
		let tag = Guard ("<cloned>");
		tag.new();
		Self {
			_tag: tag,
			val: self.val.clone(),
		}
	}
}

impl<T> Deref for Guarded<T> {
	type Target = T;

	fn deref(&self) -> &Self::Target {
		&self.val
	}
}

impl<T> DerefMut for Guarded<T> {
	fn deref_mut(&mut self) -> &mut Self::Target {
		&mut self.val
	}
}

impl<T: Eq> Eq for Guarded<T> {}

impl<T: Ord> Ord for Guarded<T> {
	fn cmp(&self, other: &Self) -> Ordering {
		self.val.cmp(&other.val)
	}
}

impl<T: PartialEq> PartialEq for Guarded<T> {
	fn eq(&self, other: &Self) -> bool {
		self.val == other.val
	}
}

impl<T: PartialOrd> PartialOrd for Guarded<T> {
	fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
		self.val.partial_cmp(&other.val)
	}
}

struct Guard (&'static str);

impl Guard {
	fn new(&self) {
		let Self (tag) = self;
		println!("tagged({})", tag);
	}
}

impl Drop for Guard {
	fn drop(&mut self) {
		let Self (tag) = self;
		println!("drop({})", tag);
	}
}
