define panic
	set $sp -= 8
	w lang rust -- set *($sp as &usize) = $pc
	set $pc = $panic
end
