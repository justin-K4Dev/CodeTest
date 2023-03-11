/**
 * Created by justin on 2016-02-12.
 */

// define the Person Class
function Person(gender) {
    this.gender = gender;
    alert('Person instantiated');
}

Person.prototype.walk = function(){
    alert ('I am walking!');
};
Person.prototype.sayHello = function(){
    alert ('hello');
};


