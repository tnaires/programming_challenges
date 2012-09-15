class Name
  attr_reader :value, :position

  def initialize(value, position)
    @value, @position = value.downcase, position
  end

  def score
    @value.chars.to_a.inject(0) {|score, char| score + letters.index(char) + 1} * @position
  end

  private

  def letters
    'abcdefghijklmnopqrstuvwxyz'
  end
end
