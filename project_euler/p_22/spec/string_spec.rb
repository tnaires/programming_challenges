require './app/string'

describe String do
  describe :unquote do
    it { '\'a string\''.unquote.should == 'a string' }
    it { '\'\''.unquote.should == '' }

    it { "\"a string\"".unquote.should == 'a string' }
    it { "\"\"".unquote.should == '' }

    it { 'a string'.unquote.should == 'a string' }
  end
end
