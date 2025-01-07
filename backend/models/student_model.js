const db=require('../database');
const bcrypt=require('bcryptjs');

const student={
    getAll:function(callback) {
        return db.query('SELECT * FROM student', callback);
    },
    getById:function(id, callback){
        return db.query('SELECT * FROM student WHERE idstudent=?',[id],callback);
    },
    add:function(student_data, callback){
        bcrypt.hash(student_data.password, 10, function(err, hashed_password){
            return db.query('INSERT INTO student(username,password,fname,lname,address) VALUES(?,?,?,?,?)',[student_data.username,hashed_password,student_data.fname, student_data.lname,student_data.address], callback);
        })
    },
    update:function(id,student_data, callback){
        bcrypt.hash(student_data.password, 10, function(err, hashed_password){
            return db.query('UPDATE student SET username=?, password=?, fname=?, lname=?, address=? WHERE idstudent=?',[student_data.username, hashed_password,student_data.fname, student_data.lname, student_data.address, id],callback);
        })
    },
    delete:function(id, callback){
        return db.query('DELETE FROM student WHERE idstudent=?',[id], callback);
    }   
}

module.exports=student;