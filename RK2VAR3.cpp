#include <iostream>
#include <iterator>
#include "vector"

class ElectronicDevice {
protected:
    std::string brand;
    std::string model;

public:
    ElectronicDevice(std::string  _brand, const std::string& _model)
            : brand(std::move(_brand)), model(_model) {}

    virtual void display() const {
        std::cout << "Brand: " << brand << ", Model: " << model << std::endl;
    }

    virtual void setNew(const std::string& newBrand, const std::string& newModel){
        brand = newBrand;
        model = newModel;
    }

    const std::string& getBrand() {
        return brand;
    }

    const std::string& getModel() {
        return model;
    }

    virtual ~ElectronicDevice() {}
};

class Smartphone : public ElectronicDevice {
private:
    std::string os;
    double os_serial;

public:

    Smartphone(const std::string& _brand, const std::string& _model, const std::string& _os, double os_serial_)
            : ElectronicDevice(_brand, _model), os(_os), os_serial(os_serial_) {}

    void display() const override {
        ElectronicDevice::display();
        std::cout << "Operating System: " << os << " " << os_serial << std::endl;
    }

    //У телефонов обновляем прошивку
    void setNew(const std::string& newBrand, const std::string& newModel) override {
        ElectronicDevice::setNew(newBrand, newModel);
        this->os_serial += 1;
    }
};

class Laptop : public ElectronicDevice {
private:
    double screenSize;
    double battery_capacity;

public:

    Laptop(const std::string& _brand, const std::string& _model, double _screenSize, double battery_capacity_)
            : ElectronicDevice(_brand, _model), screenSize(_screenSize), battery_capacity(battery_capacity_){}

    void display() const override {
        ElectronicDevice::display();
        std::cout << "Screen Size: " << screenSize << " inches. Battery_capacity: " <<  battery_capacity << "mAh" << std::endl;
    }

    //У ноутбуков изменяем ёмкость аккумулятора
    void setNew(const std::string& newBrand, const std::string& newModel) override {
        ElectronicDevice::setNew(newBrand, newModel);
        this->battery_capacity *= 1.2;
    }

};

// Функция для изменения характеристик устройства
void modifyDevice(ElectronicDevice* device) {
    device->setNew("Updated " + device->getBrand(), device->getModel());
}


int main() {
    std::vector<ElectronicDevice*> devices;

    //Заполняем вектора какими-то устройствами
    devices.push_back(new Smartphone("Samsung", "Galaxy S21", "Android", 11));
    devices.push_back(new Smartphone("Xiaomi", "MI 9T PRO", "Android", 10));
    devices.push_back(new Smartphone("OnePlus", "9 PRO", "Android", 13));
    devices.push_back(new Smartphone("Apple", "iPhone 13", "iOS", 16.2));
    devices.push_back(new Smartphone("Apple", "iPhone 6", "iOS", 11.2));

    devices.push_back(new Laptop("Lenovo", "IdealPad 5", 14.1, 42000));
    devices.push_back(new Laptop("MacBook", "Air 13", 13.3, 34050));
    devices.push_back(new Laptop("Samsung", "UltraBook", 15.6, 39000));
    devices.push_back(new Laptop("MacBook", "Pro 16 M2", 16.2, 64500));
    devices.push_back(new Laptop("Xiaomi", "GamingTurbo", 15.6, 23000));

    //Выводим информацию о каждом устройстве при помощи итераторов
    //Ниже переменная it имеет тип "std::iterator<ElectronicDevice**, std::vector <ElectronicDevice*>>", пользуемся auto, чтобы было короче
    for (auto it = devices.begin(); it != devices.end(); ++it) {
        (*it)->display();
    }

    //Обновляем все устройства
    for (auto it = devices.begin(); it != devices.end(); ++it) {
        modifyDevice(*it);
    }

    //Выводим информацию об обновлённых устройствах
    for (auto it = devices.begin(); it != devices.end(); ++it) {
        (*it)->display();
    }

    //Освободим память
    for (auto it = devices.begin(); it != devices.end(); ++it) {
        delete *it;
    }

    return 0;
}