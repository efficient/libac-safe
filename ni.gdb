eval "ni %d", $count - 1
w lang c -- if !$_any_caller_is($frame, 15)
	q 1
end
if $count != 0
	ni
end
