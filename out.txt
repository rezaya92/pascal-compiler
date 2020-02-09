@.str.1 = private unnamed_addr constant [13 x i8] c"not equal ! \00", align 1
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"
define void @write(i8* %toprint) {
%1 = alloca i8*, align 8
store i8* %toprint, i8** %1, align 8
%2 = load i8*, i8** %1, align 8
%3 = call i32 (i8*, ...) @printf(i8* %2)
ret void
}
declare i32 @printf(i8*, ...)
define i32 @main( )
{
%a = alloca i32, align 1
%1 = alloca i32, align 1
store i32 2, i32* %1, align 1
%2 = load i32, i32* %1, align 1
store i32 2, i32* %a, align 1

%b = alloca i32, align 1
%3 = alloca i32, align 1
store i32 3, i32* %3, align 1
%4 = load i32, i32* %3, align 1
store i32 4, i32* %b, align 1

%c = alloca float, align 1

%5 = alloca i8*, align 1
store i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i32 0, i32 0), i8** %5, align 1
%6 = load i8*, i8** %5, align 1
call void @write(i8* %6)

%7 = alloca i32, align 1
store i32 0, i32* %7, align 1
%8 = load i32, i32* %7, align 1
ret i32 %8

}
