define panic
	w lang rust -- set $misaligned = ($sp as usize) % 16
	set $sp -= 8
	w lang rust -- set *($sp as &usize) = $pc
	if $misaligned
		set $pc = $realign
	else
		set $pc = $panic
	end
end
