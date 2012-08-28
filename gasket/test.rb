require 'cairo'

CX = 512
CY = 512

surface = Cairo::ImageSurface.new(CX, CY)
context = Cairo::Context.new(surface)

context.set_source_rgb(0, 0, 0) # 黒
context.rectangle(0, 0, CX, CY)
context.fill

$drawTriangle_bind = lambda{||
	c = context
	lambda {|x, y, w|
		drawTriangle(x, y, w, c)
	}
}
$drawTriangle_c = $drawTriangle_bind.call
$drawTriangle_curry = lambda{|x|
	lambda{|y|
		lambda{|w|
			$drawTriangle_c.call(x, y, w)
		}
	}
}


def drawTriangle(lx, ly, w, context)

	if w < 0.01
		return
	end

	root3 = 1.7320504
	tx = lx + w/2
	ty = ly + w*(root3/2)

	rx = lx + w
	ry = ly

	context.set_source_color(Cairo::Color::BLACK)
	context.move_to(lx, ly)
	context.line_to(rx, ry)
	context.line_to(tx, ty)
	context.fill
	context.set_source_color(Cairo::Color::BLUE)
	context.stroke

	nw = w/2
	nllx = lx - nw/2
	t = nw*Math.sin(PI/3)
	nlly = ly + t
	$drawTriangle_curry.call(nllx).call(nlly).call(nw)

	nrlx = rx - nw/2
	nrly = nlly
	$drawTriangle_c.call(nrlx, nrly, nw)	

	ntlx = ( (rx + lx)/2 + lx )/2
	ntly = ly - t
	$drawTriangle_c.call(ntlx, ntly, nw)	


end

def drawRoot(context)

	context.set_source_color(Cairo::Color::WHITE)
	context.move_to(LX, LY)
	context.line_to(RX, RY)
	context.line_to(TX, TY)
	context.fill
	context.set_source_color(Cairo::Color::BLUE)
	context.stroke

end


my = 10

PI = 3.1415

W = 512
LX = 0 
LY = CY  - my
RX = LX + W
RY = LY 
TX = (RX + LX)/2
TY = RY - W*Math.sin(PI/3)

drawRoot(context)

lx = (LX + TX) / 2
ly = (LY + TY) / 2
w = W/2
#drawTriangle(lx, ly, w, context)
$drawTriangle_c.call(lx, ly, w)




surface.write_to_png('polygon.png')
