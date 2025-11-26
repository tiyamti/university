# گزارش تست درخواست‌ها
#موسوی 4013623019
## 1. درخواست به `http://localhost:5000`
ارسال یک درخواست ساده به سرور لوکال برای بررسی وضعیت سرویس و اطمینان از فعال بودن API.
<img width="1919" height="1032" alt="Screenshot 2025-11-26 115721" src="https://github.com/user-attachments/assets/15d354db-1f71-49e7-b23a-2f39073b6773" />

## 2. ارسال درخواست لاگین به اسنپ
ارسال اطلاعات اولیه لاگین (شماره تلفن یا اطلاعات کاربر) برای شروع فرآیند احراز هویت.
<img width="1911" height="882" alt="Screenshot 2025-11-26 122153" src="https://github.com/user-attachments/assets/1efe70b3-19d4-43f1-999a-ad1cc716cf06" />


## 3. ثبت شماره و ارسال OTP
ثبت شماره تلفن کاربر در سرور و دریافت کد یکبارمصرف (OTP) جهت ادامه احراز هویت.
<img width="1918" height="885" alt="Screenshot 2025-11-26 122300" src="https://github.com/user-attachments/assets/d1db6c3e-5c7c-4cc8-ac5d-371dd660546f" />

## 4. ارسال درست OTP
وارد کردن کد صحیح ارسال‌شده و تکمیل مرحله تأیید هویت با موفقیت.
<img width="1919" height="893" alt="Screenshot 2025-11-26 122559" src="https://github.com/user-attachments/assets/1e0e08ab-a1e5-4a33-b672-8442ea33ce79" />

## 5. ارسال اشتباه OTP
ارسال کد اشتباه برای بررسی واکنش سرور و تشخیص مکانیزم‌های امنیتی و خطاها.
<img width="1919" height="882" alt="Screenshot 2025-11-26 122350" src="https://github.com/user-attachments/assets/9e75549e-53e8-4106-bfde-6dc8d3402dde" />

## 6. ارسال چندین OTP
ارسال چندین درخواست OTP برای بررسی محدودیت‌ها، Rate Limit و جلوگیری از سوءاستفاده.
<img width="1510" height="835" alt="Screenshot 2025-11-26 124924" src="https://github.com/user-attachments/assets/2fccdd4b-d360-4bd3-9de9-d3c46c2aba17" />
<img width="1919" height="889" alt="Screenshot 2025-11-26 125420" src="https://github.com/user-attachments/assets/76f6afef-93cb-4aec-b0c1-75f6f27cc6c8" />
<img width="1917" height="882" alt="Screenshot 2025-11-26 131439" src="https://github.com/user-attachments/assets/b8d202ff-e8ac-4908-a3e7-6bcdc8ef00c2" />
## پاسخ‌ها

* **کد وضعیت HTTP:** `429 Too Many Requests`
* **بدنه پاسخ:**

```json
{
  "type": "BAD_REQUEST",
  "message": {
    "title": "TooManyRequests",
    "message": "تعداد تلاش‌های شما از حد مجاز گذشته است، لطفا بعد از دو ساعت دوباره تلاش کنید."
  },
  "error_code": "000001"
}
```

---

## هدرهای امنیتی غایب / بررسی نشده

* `X-Frame-Options`: غایب
* `Content-Security-Policy`: غایب
* `Strict-Transport-Security`: وجود دارد (HSTS فعال)
* سایر هدرهای امنیتی مهم مانند `X-Content-Type-Options` و `Referrer-Policy`: غایب

---

## پیام‌های خطا و اطلاعات حساس

* پیام خطا فقط می‌گوید تعداد تلاش‌ها از حد مجاز گذشته است.
* هیچ اطلاعاتی درباره موجود یا ناموجود بودن حساب یا جزئیات کاربر فاش نمی‌شود.
* بنابراین اطلاعات حساس لو نرفته است.

---

## نکات امنیتی

* غیبت `X-Frame-Options` و `Content-Security-Policy` همچنان ریسک **clickjacking** و **XSS** را ایجاد می‌کند.
* پیام خطا امن است و هیچ اطلاعات حساسی لو نمی‌دهد.
* **محدودیت نرخ (rate limit)** درست اعمال شده و پیغام مناسبی ارائه می‌دهد.

### نبود هدرهای امنیتی (CSP و X-Frame-Options)

شرح: پاسخ‌های API فاقد هدرهای حیاتی مثل Content-Security-Policy و X-Frame-Options هستند.
ریسک:

امکان Clickjacking

امکان اجرای XSS در صورت بروز هرگونه تزریق در فرانت‌اند
شدت: Medium
PoC:

Embed کردن endpoint در iframe برای Clickjacking

استفاده از JSON ورودی به صورت ناامن برای تست XSS chain


###  رفتار صحیح امنیتی: HSTS فعال

شرح: هدر HSTS با max-age بالا فعال است.
نتیجه: این مورد Bug نیست و یک اقدام مثبت امنیتی محسوب می‌شود.


### افشای الگوی Rate Limit (429 Too Many Requests)

شرح: پیام خطای 429 اطلاعات دقیقی درباره محدودیت درخواست ارائه می‌دهد.
ریسک: مهاجم راحت‌تر می‌تواند زمان‌بندی حملات brute-force را تنظیم کند.
شدت: Low
PoC: ارسال پشت‌سرهم چندین درخواست تا دریافت پاسخ 429.


