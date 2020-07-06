<?php 

$width = 24;
$height = 8; 

$data = "7F0808087F0038545454180000417F40000000417F400000";

$framebuffer = []; 

// init
for ($y=0; $y < $height; $y++)
{ 
	for ($x=0; $x < $width; $x++)
	{ 
		if (!isset($framebuffer[$y]))
		{
			$framebuffer[$y] = []; 
		}
		$framebuffer[$y][$x] = 0;
	}
}

for ($x=0; $x < $width; $x++)
{ 
	$row = hexdec($data[$x * 2] . $data[($x * 2) + 1]);

	for ($y=0; $y < $height; $y++)
	{
		if (($row >> $y) & 1)
		{
			$framebuffer[$y][$x] = 1;
		}
	}
}

// render
for ($y=0; $y < $height; $y++)
{ 
	for ($x=0; $x < $width; $x++)
	{
		if ($framebuffer[$y][$x])
		{
			echo "\xE2\x96\x88";
		}
		else
		{
			echo "\xE2\x96\x91";
		}
	}
	echo "\n";
}


