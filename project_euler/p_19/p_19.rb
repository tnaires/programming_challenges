require 'date'

d1 = Date.new(1901, 1, 1)
d2 = Date.new(2000, 12, 31)
sunday_count = 0

(d1..d2).each do |date|
  sunday_count += 1 if date.sunday? && date.day == 1
end

puts sunday_count
