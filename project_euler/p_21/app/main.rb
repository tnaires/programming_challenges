require './app/fixnum'

amicable = []

2.upto(10_000) do |n|
  divisors_sum = n.proper_divisors.inject(:+)
  
  amicable << n if divisors_sum.amicable?(n) 
end

puts amicable.inject(:+)
