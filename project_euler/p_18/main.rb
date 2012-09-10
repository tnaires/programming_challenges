class Cell
  attr_reader :value
  attr_accessor :sum

  def initialize(value)
    @value = value
    @sum = value
  end
end

input_path = "#{File.expand_path(File.dirname(__FILE__))}/input_67.txt"
lines = IO.readlines(input_path)
rows = []

lines.each_index do |line_index|
  line = lines[line_index]
  cells = line.split
  row = []

  cells.each_index do |value_index|
    value = cells[value_index].to_i
    cell = Cell.new(value)

    unless line_index == 0
      parent_index_1 = value_index
      parent_index_2 = value_index - 1

      if parent_index_2 < 0
        cell.sum += rows[line_index - 1][0].sum
      elsif parent_index_1 > line_index - 1
        cell.sum += rows[line_index - 1][line_index - 1].sum
      else
        sum_1 = rows[line_index - 1][parent_index_1]
        sum_2 = rows[line_index - 1][parent_index_2]
        cell.sum += [sum_1.sum, sum_2.sum].max
      end
    end

    row << cell
  end

  rows << row
end

puts rows[lines.size - 1].map(&:sum).max
