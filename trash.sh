for i do
	mkdir -p ~/Trash/$(date +%Y_%b._%d_%H:%M:%S)_$i & mv $i ~/Trash/$(date +%Y_%b._%d_%H:%M:%S)_$i/
done
