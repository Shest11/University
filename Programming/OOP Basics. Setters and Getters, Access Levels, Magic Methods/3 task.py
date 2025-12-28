class IPAddress:
    def __init__(self, ip):
        if isinstance(ip, str):
            self.ip_address = ip.split('.')
        elif isinstance(ip, (list, tuple)):
            self.ip_address = ip
        else:
            raise TypeError("IP-адрес должен быть строкой, списком или кортежем")

        if len(self.ip_address) > 4:
            raise ValueError("IP-адрес должен иметь 4 числа")

        for i in self.ip_address:
            if not isinstance(i, int):
                if isinstance(i, str):
                    i = int(i)
                else:
                    raise ValueError("Части IP-адреса должны быть целыми числами")
            else:
                if i < 0 or i > 255:
                    raise ValueError("Части IP-адреса должны быть от 0 до 255")

    def __str__(self):
        return '.'.join(map(str, self.ip_address))

    def __repr__(self):
        return f'IPAddress({self})'


ip1 = IPAddress(['1.3', 123, 13, 44])
ip2 = IPAddress('1.1.1.1')

print(ip1)
print(ip2)

print(repr(ip1))
print(repr(ip2))