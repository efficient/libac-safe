define panic
	set $sp -= 8
	set *($sp as &usize) = $pc
	set $pc = $panic
end
