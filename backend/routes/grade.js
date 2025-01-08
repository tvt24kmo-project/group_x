const express = require('express');
const router = express.Router();
const grade = require('../models/grade_model');



router.get('/:uname', function(request, response){
    grade.getByUname(request.params.uname,function(err, result){
        if(err){
            response.json(err);
        }
        else {
            response.json(result);
        }
    })
});


module.exports=router;

