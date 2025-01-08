const db=require('../database');

const student={
    getByUname:function(uname,callback) {
        return db.query('SELECT name,ects,grade,date_format(grade_date,"%d.%m.%Y") AS "grade_date" FROM course INNER JOIN grade ON course.idcourse=grade.idcourse INNER JOIN student ON grade.idstudent=student.idstudent WHERE username=?',[uname], callback);
    } 
}

module.exports=student;