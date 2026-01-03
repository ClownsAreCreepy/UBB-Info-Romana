class Car:
    def __init__(self,eng,col):
        """
          Initialize a car
          eng - engine
          col - string, ie White
        """
        self.__engine = eng
        self.__color = col
    def getColor(self):
        """
          Getter method for color
          return string
        """
        return self.__color
    def getEngine(self):
        """
          Getter method for engine
          return engine
        """
        return self.__engine


class Engine:
    def __init__(self, cap, type):
        """
          initialize the engine
          cap positive integer
          type string
        """
        self.__capacity = cap
        self.__type = type

    def getCapacity(self):
        """
       Getter method for the capacity
        """
        return self.__capacity

    def getType(self):
        """
         Getter method for type
         return string
        """
        return self.__type