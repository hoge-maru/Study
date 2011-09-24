#!/usr/bin/ruby

require 'optparse'

$path = "/home/y-ishimaru/git/Study/remove/hoge/"
$max = 10

opt = OptionParser.new
opt.on('-n VAL'){|v|
	$max = v.to_i
}
opt.on('-p VAL'){|v|
	$path = v
}
opt.parse!(ARGV)

entries = Dir::entries($path)
entries.delete_if { |x| /.*\.$/ =~ x }
num = entries.length

if num < $max
	exit
end

entries.sort! do |a, b|
  File.stat($path + a).mtime.strftime("%Y%m%d%H%M%S") <=>
  File.stat($path + b).mtime.strftime("%Y%m%d%H%M%S")
end

for i in 0..$max/2
	fname = entries.shift
	if fname =~ /.*zip/
		delpath = $path + fname
		File.delete delpath
	end
end

