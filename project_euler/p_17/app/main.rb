require './app/fixnum'

sum = 0

(1..1000).each do |e|
  sum += e.in_full.delete(' ').delete('-').length
end

puts sum
