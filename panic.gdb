define panic
	w lang rust -- set $returned = $pc == *($sp as &usize - 1)
	if $returned
		set $pc += 1
	end

	w lang rust -- set $misaligned = ($sp as usize) % 16
	set $sp -= 8
	w lang rust -- set *($sp as &usize) = $pc
	if $misaligned
		set $pc = $realign
	else
		set $pc = $panic
	end
end
