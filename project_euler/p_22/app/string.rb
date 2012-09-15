class String
  def unquote
    result = self.clone
    result.unquote!
    result
  end

  def unquote!
    self.delete!('\'')
    self.delete!("\"")
  end
end
