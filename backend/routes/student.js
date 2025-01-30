const express = require('express');
const router = express.Router();
const student = require('../models/student_model');

router.get('/', function(request, response){
    student.getAll(function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result);
        }
    })
});

router.get('/:uname', function(request, response){
    student.getById(request.params.uname,function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result[0]);
        }
    })
});

router.post('/',function(request, response){
    student.add(request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

router.put('/:id',function(request, response){
    student.update(request.params.id,request.body, function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:id',function(request, response){
    student.delete(request.params.id, function(err,result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result.affectedRows);
        }  
    })
});

module.exports=router;