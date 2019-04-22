import xml.parsers.expat

class ExParser(object):
    '''Parse roster xml'''
    def __init__(self, xml_raw):
        '''init parser and setup handlers'''
        self.parser = xml.parsers.expat.ParserCreate()

        #connect handlers
        self.parser.StartElementHandler = self.start_element
        self.parser.EndElementHandler = self.end_element
        self.parser.CharacterDataHandler = self.char_data
        self.parser.Parse(xml_raw)
        del(xml_raw)

    def start_element(self, name, attrs):
        '''Start xml element handler'''
        print 'start:'+name

    def end_element(self, name):
        '''End xml element handler'''
        print 'end:'+name

    def char_data(self, data):
        '''Char xml element handler'''
        print 'data is '+data
