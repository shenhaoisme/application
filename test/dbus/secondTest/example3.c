#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus.h>
 
static void abort_on_error(DBusError *error);
static DBusMessage *create_property_get_message(const char *bus_name, const char *path, const char *iface, const char *propname);
static double extract_double_from_variant(DBusMessage *reply, DBusError *error);
static double get_double_property(DBusConnection *connection, const char *bus_name, const char *path, const char *iface, const char *propname, DBusError *error);
 
int main() {
    DBusConnection *connection = NULL;
    DBusError error;
    double energy = 0;
    double fullEnergy = 0;
 
    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SYSTEM, &error);
    abort_on_error(&error);
 
    energy = get_double_property(connection, "org.freedesktop.UPower",
                     "/org/freedesktop/UPower/devices/battery_BAT1",
                     "org.freedesktop.UPower.Device",
                     "Energy",
                     &error);
    abort_on_error(&error);
 
    fullEnergy = get_double_property(connection, "org.freedesktop.UPower",
                     "/org/freedesktop/UPower/devices/battery_BAT1",
                     "org.freedesktop.UPower.Device",
                     "EnergyFull",
                     &error);
     
    abort_on_error(&error);
 
    printf("%lf", (energy*100)/fullEnergy);
 
    return 0;
}
 
static void abort_on_error(DBusError *error) {
    if (dbus_error_is_set(error)) {
        fprintf(stderr, "%s", error-&gt;message);
        abort();
    }
}
// 基本类型是：

// byte (type y);
// boolean (type b);
// int/uint 16/32 bit (type n,q,i,u);
// double (type d);
// unix_fd (type h);
// string (type s);
// object_path (type o);
// signature (type g).


// 如您所见，每种基本类型都由类型字符标识。此类型字符用于方法和方法参数以及结果类型的签名。现在我们将看到容器类型：

// struct (type ([field types]), ad ex. a struct composed of two fields, a string and an integer, has type (sn));
// array (type a[element type], ad ex. an array of integers has the type an);
// variant (type v);
// dict (type {[key type][value type]}, ad ex. a dictionary that maps strings to integers has type {sn}).
// 因此，除variant 类型外，每个容器类型都有一个由两个或多个字符组成的签名。
// 变体类型确实很奇怪，因为它可以表示每个有效的DBus类型，并且消息将包含实际传递值的签名。变体类型非常有用，因为它使DBus能够管理属性。这是org.freedesktop.DBus.Properties接口的d-feet表示：
