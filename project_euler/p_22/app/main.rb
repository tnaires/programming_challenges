require './app/name'
require './app/string'

lines = IO.readlines('./app/input.txt')
words = lines[0].split(',').map(&:unquote).sort.map(&:chomp)
total_score = 0

words.each_index do |index|
  name = Name.new(words[index], index + 1)
  total_score += name.score
end

puts total_score
