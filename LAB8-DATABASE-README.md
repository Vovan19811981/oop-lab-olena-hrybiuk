# Практична робота № 8: Доступ до бази даних

## Тема

Доступ до бази даних

## Мета

Навчитися створювати додатки в C++ Builder з допомогою редактора полів при установці полів підстановки, придбати практичні навички у програмній реалізації управління даними.

## Завдання

1. Викликати редактор полів і відобразити імена полів таблиць, раніше створених у попередній роботі
2. Створити поля для перегляду всіх пов'язаних підлеглих полів таблиць
3. Налаштувати поля і призначити властивості полів за допомогою редактора полів (подання дати, ширини поля, зміна заголовка поля, введення початкового значення при створенні нових рядків)
4. Використовуючи можливості редактора полів, створити додаток, що реалізує подання даних у вигляді форми
5. Організувати програмне керування даними: вставку, редагування, видалення, збереження, скасування змін
6. Виконати програмну реалізацію сортування різних типів полів
7. Відфільтрувати записи різних типів полів за певними критеріями
8. З допомогою різних методів знайти записи за певними критеріями

## Структура бази даних

### Таблиця "Касети"
- `Код_Кассеты` - первинний ключ
- `Наименование` - назва касети
- `Тип_Касcеты` - тип/жанр
- `Цена` - ціна прокату

### Таблиця "Клієнт"
- `Код_Клиента` - первинний ключ
- `Фио` - ПІБ клієнта
- `Информация` - додаткова інформація

### Таблиця "Пункт_Проката"
- `Код_прокаты` - первинний ключ
- `Код_кассеты` - зовнішній ключ (FK до Касети)
- `Код_Клиента` - зовнішній ключ (FK до Клієнт)
- `Дата_Выдачи` - дата видачі
- `Дата_Приема` - дата прийому
- `Количество_Копій` - кількість копій
- `Дата_Возврата` - дата повернення
- `Отметка_возврата` - мітка повернення (boolean)

## Технології

- **IDE**: C++ Builder
- **База даних**: Microsoft Access (Video.mdb)
- **Компоненти**:
  - ADOConnection
  - ADOTable (AT1, AT2, AT3)
  - ADOQuery (ADOQ1, ADOQ2)
  - DataSource (DS1, DS2, DS3)
  - DBGrid, DBNavigator
  - DBEdit, DBLookupComboBox, DBCheckBox
  - PageControl, Panel, Button, Memo

## Хід роботи

### 1. Використання значень станів НД (набір даних)

#### Управління даними

**Вставка запису**
```cpp
void __fastcall TForm1::Button2Click(TObject *Sender) {
    DM2->AT1->Insert();
}
```

**Редагування**
```cpp
void __fastcall TForm1::Button3Click(TObject *Sender) {
    DM2->AT1->Edit();
}
```

**Видалення з підтвердженням**
```cpp
void __fastcall TForm1::Button4Click(TObject *Sender) {
    char s[200]="Вы действительно хотите удалить кассету\n";
    AnsiString s2=DM2->AT1->FieldByName("Наименование")->AsString;
    char *s1=s2.c_str();
    if (Application->MessageBox(strcat(s,s1), "Внимание!!!", MB_OKCANCEL)==IDOK)
        DM2->AT1->Delete();
}
```

**Скасування змін**
```cpp
void __fastcall TForm1::Button5Click(TObject *Sender) {
    DM2->AT1->Cancel();
}
```

**Збереження змін**
```cpp
void __fastcall TForm1::Button6Click(TObject *Sender) {
    if (DM2->AT1->Modified)
        DM2->AT1->Post();
}
```

#### Методи навігації

- `First` - перейти до першого запису
- `Prior` - перейти до попереднього запису
- `Next` - перейти до наступного запису
- `Last` - перейти до останнього запису
- `MoveBy(int M)` - переміститися на M записів

**Приклад переміщення**
```cpp
DM2->AT1->Next();  // Наступний запис
```

#### Перевірка наявності записів

```cpp
if (!(DM2->AT1->IsEmpty())) {
    // НД містить записи
}
```

**Функції EOF і BOF**:
- `EOF` (End Of File) - повертає `True`, якщо курсор за останнім записом
- `BOF` (Beginning Of File) - повертає `True`, якщо курсор на першому записі

#### Послідовна обробка НД (вперед)

```cpp
if (!(DM2->AT1->IsEmpty())) {
    DM2->AT1->First();
    while (!DM2->AT1->Eof) {
        Memo1->Lines->Add(DM2->AT1->Fields->Fields[1]->AsString + " " +
                          DM2->AT1->Fields->Fields[2]->AsString);
        DM2->AT1->Next();
    }
}
```

#### Послідовна обробка НД (назад)

```cpp
DM2->AT1->Last();
while (!DM2->AT1->Bof) {
    Memo2->Lines->Add((AnsiString)DM2->AT1->Fields->Fields[1]->Value + " " +
                      DM2->AT1->FieldByName("Цена")->AsString);
    DM2->AT1->Prior();
}
```

#### Метод SetFields

**Редагування поточного запису**
```cpp
DM2->AT1->Edit();
DM2->AT1->SetFields(ARRAYOFCONST((
    DM2->AT1->Fields->Fields[0]->Value,
    DM2->AT1->Fields->Fields[1]->Value,
    "Мультики-фильм")));
DM2->AT1->Post();
```

**Додавання нового запису в кінець**
```cpp
AnsiString s = Memo1->Text;
DM2->AT1->Append();
DM2->AT1->SetFields(ARRAYOFCONST(("007","Враги","Боевик",4.50,s)));
DM2->AT1->Post();
```

**Використання AppendRecord**
```cpp
DM2->AT1->AppendRecord(ARRAYOFCONST(("009",
    "Маршрут-2","Боевик",4.30,"Продолжение маршрута")));
DM2->AT1->Edit();
DM2->AT1->Post();
```

### 2. Зв'язування таблиць

#### Налаштування DBLookupComboBox

**Властивості для зв'язування**:
- `DataSource` - джерело даних підлеглої таблиці (DM2->DS3)
- `DataField` - поле вторинного ключа ("Код_Кассеты")
- `ListSource` - джерело даних головної таблиці (DM2->DS1)
- `ListField` - поле для відображення ("Наименование")
- `KeyField` - поле первинного ключа ("Код_Касcеты")

**Програмне налаштування**
```cpp
void __fastcall TForm1::Button10Click(TObject *Sender) {
    DBLookupComboBox1->DataSource = DM2->DS3;
    DBLookupComboBox1->DataField = "Код_Кассеты";
    DBLookupComboBox1->ListSource = DM2->DS1;
    DBLookupComboBox1->ListField = "Наименование";
    DBLookupComboBox1->KeyField = "Код_Касcеты";
    
    DBLookupComboBox2->DataSource = DM2->DS3;
    DBLookupComboBox2->DataField = "Код_Клиента";
    DBLookupComboBox2->ListSource = DM2->DS2;
    DBLookupComboBox2->ListField = "Фио";
    DBLookupComboBox2->KeyField = "Код_Клиента";
}
```

**Роз'єднання таблиць**
```cpp
void __fastcall TForm1::Button11Click(TObject *Sender) {
    DBLookupComboBox1->DataSource = NULL;
    DBLookupComboBox1->DataField = "";
    DBLookupComboBox1->ListSource = NULL;
    DBLookupComboBox2->DataSource = NULL;
    DBLookupComboBox2->DataField = "";
    DBLookupComboBox2->ListSource = NULL;
}
```

#### Зв'язування Master-Detail

**Через редактор зв'язків полів**:
1. Встановити `Active` = `False` для підлеглої таблиці
2. У властивості `MasterSource` вказати головну таблицю
3. Клацнути на `MasterFields` → відкриється редактор
4. Вибрати поля у вікнах Detail Fields та Master Fields
5. Натиснути Add
6. Встановити `Active` = `True`

**Програмне зв'язування (Касети - Пункт_Проката)**
```cpp
void __fastcall TForm1::Button9Click(TObject *Sender) {
    DM2->AT3->Close();
    DM2->AT3->MasterSource = NULL;
    DM2->AT3->MasterFields = "";
    DM2->AT3->IndexFieldNames = "";
    DBLookupComboBox1->DataSource = NULL;
    
    DM2->AT3->MasterSource = DM2->DS1;
    DM2->AT3->MasterFields = "Код_Касcеты";
    DM2->AT3->IndexFieldNames = "Код_кассеты";
    DM2->AT3->Open();
}
```

**Зв'язування (Клієнт - Пункт_Проката)**
```cpp
void __fastcall TForm1::Button12Click(TObject *Sender) {
    DM2->AT3->Close();
    DM2->AT3->MasterSource = NULL;
    DM2->AT3->MasterFields = "";
    DM2->AT3->IndexFieldNames = "";
    DBLookupComboBox2->DataSource = NULL;
    
    DM2->AT3->MasterSource = DM2->DS2;
    DM2->AT3->MasterFields = "Код_Клиента";
    DM2->AT3->IndexFieldNames = "Код_Клиента";
    DM2->AT3->Open();
}
```

**Скасування всіх зв'язків**
```cpp
void __fastcall TForm1::Button13Click(TObject *Sender) {
    DM2->AT3->Close();
    DM2->AT3->MasterSource = NULL;
    DM2->AT3->MasterFields = "";
    DM2->AT3->IndexFieldNames = "";
    DM2->AT3->Open();
}
```

### 3. Створення обчислюваних полів

#### Процес створення

1. Встановити `Active` = `False` для таблиці
2. Викликати редактор полів (подвійне клацання на компоненті)
3. Правою кнопкою → New Fields
4. Заповнити:
   - `Name` - ім'я поля
   - `Type` - тип даних
   - `Size` - розмір (для рядків)
   - Field type → обрати `Calculated`
5. Встановити `Active` = `True`
6. Створити подію `OnCalcFields`

**Приклад: об'єднання назви та ціни**
```cpp
void __fastcall TDM2::AT1CalcFields(TDataSet *DataSet) {
    DM2->AT1->FieldByName("Прайс_Лист")->AsString = 
        DM2->AT1->FieldByName("Наименование")->AsString + " - " +
        FloatToStr(DM2->AT1->FieldByName("Цена")->AsFloat) + " грн.";
}
```

#### Обчислюване поле з двох таблиць

**Створення поля підстановки для ціни**:
1. В редакторі полів → New Field
2. Name = "Ціна", Type = float
3. Field type → Lookup
4. KeyFields = "Код_Кассеты"
5. Dataset = AT1
6. Lookup Keys = "Код_Касcеты"
7. Result Field = "Ціна"

**Створення обчислюваного поля "Сума"**
```cpp
void __fastcall TDM2::AT3CalcFields(TDataSet *DataSet) {
    DM2->AT3->Fields->Fields[10]->Value = 
        DM2->AT3->Fields->Fields[8]->Value * 
        DM2->AT3->Fields->Fields[9]->Value;
}
```

### 4. Сортування полів

**Синтаксис**:
```cpp
ADOTable1->IndexFieldNames = "ім'я поля";
```

**Приклад для головної таблиці**
```cpp
void __fastcall TForm1::Button16Click(TObject *Sender) {
    AnsiString s = ComboBox1->Text;
    DM2->AT1->IndexFieldNames = s;
}
```

**Приклад для підлеглої таблиці**
```cpp
void __fastcall TForm1::Button17Click(TObject *Sender) {
    char s[30];
    strcpy(s, ComboBox2->Text.c_str());
    DM2->AT3->IndexFieldNames = s;
}
```

**Скасування сортування**:
```cpp
DM2->AT1->IndexFieldNames = "";
```

### 5. Фільтрація даних

#### Властивості
- `Filter` - умови відбору
- `Filtered` - увімкнення/вимкнення фільтрації

**Важливо**: 
- Імена полів відокремлюються пробілами від операторів
- Перед фільтрацією рекомендується сортувати поля

#### Фільтрація за частковим збігом

```cpp
void __fastcall TForm1::Edit4Change(TObject *Sender) {
    if (Edit4->Text.Length()>0 && CheckBox1->Checked) {
        DM2->AT1->IndexFieldNames = "Наименование";
        DM2->AT1->Filtered = True;
        DM2->AT1->Filter = AnsiString("Наименование > '" + Edit4->Text + "'");
    } else {
        DM2->AT1->IndexFieldNames = "";
        DM2->AT1->Filtered = False;
    }
}
```

#### Фільтрація за діапазоном дат

```cpp
void __fastcall TForm1::CheckBox2Click(TObject *Sender) {
    if (CheckBox3->Checked) {
        DM2->AT3->MasterFields = "";
        DM2->AT3->IndexFieldNames = "Дата_Приема";
        DM2->AT3->Filtered = True;
    } else {
        DM2->AT3->IndexFieldNames = "";
        DM2->AT3->Filtered = False;
    }
    DM2->AT3->Filter = "(Дата_Приема >= '" + Edit5->Text + 
                       "' and Дата_Приема <= '" + Edit6->Text + "')";
}
```

**Приклади фільтрів**:
```cpp
// OR
"(Дата_Приема = '" + Edit5->Text + "' or Дата_Приема = '" + Edit6->Text + "')"

// NOT EQUAL
"(Дата_Приема <> '" + Edit5->Text + "' and Дата_Приема <> '" + Edit6->Text + "')"
```

### 6. Пошук записів

#### Метод Locate

**Оголошення**:
```cpp
virtual bool __fastcall Locate(const AnsiString KeyFields, 
                               const System::Variant &KeyValues, 
                               TLocateOptions Options);
```

**Параметри**:
- `KeyFields` - список полів для пошуку
- `KeyValues` - масив значень
- `Options` - опції:
  - `loCaseInsensitive` - нечутливість до регістру
  - `loPartialKey` - частковий збіг

**Приклад: пошук за прізвищем**
```cpp
void __fastcall TForm1::Edit7Change(TObject *Sender) {
    TLocateOptions Opts;
    Opts << loPartialKey << loCaseInsensitive;
    DM2->AT2->Locate("Фио", Edit7->Text, Opts);
}
```

**Пошук з встановленням зв'язку**
```cpp
void __fastcall TForm1::Button18Click(TObject *Sender) {
    AnsiString s;
    TLocateOptions Opts;
    Opts << loPartialKey << loCaseInsensitive;
    s = Edit7->Text;
    DM2->AT2->Locate("Фио", s, Opts);
    
    if (flag) {
        DM2->AT3->Close();
        DM2->AT3->MasterSource = NULL;
        DBLookupComboBox2->DataSource = NULL;
        DM2->AT3->MasterFields = "";
        DM2->AT3->IndexFieldNames = "";
        DM2->AT3->MasterSource = DM2->DS2;
        DM2->AT3->IndexFieldNames = "Код_Клиента";
        DM2->AT3->MasterFields = "Код_Клиента";
        DM2->AT3->Open();
        flag = !flag;
    } else {
        DM2->AT3->Close();
        DM2->AT3->MasterSource = NULL;
        DM2->AT3->MasterFields = "";
        DM2->AT3->IndexFieldNames = "";
        DM2->AT3->Open();
        flag = !flag;
    }
}
```

**Пошук за двома полями**
```cpp
void __fastcall TForm1::Button19Click(TObject *Sender) {
    TLocateOptions Opts;
    AnsiString s1, s2;
    s2 = ComboBox3->Text;
    s1 = s2.SubString(1, s2.Pos(" ")-1);
    
    Variant TextP[2];
    TextP[0] = Edit9->Text;
    TextP[1] = s1;
    
    DM2->AT3->First();
    if (!DM2->AT3->Locate("Дата_Приема;Код_Клиента", 
                          VarArrayOf(TextP,1), Opts)) {
        ShowMessage("Таких данных нет!");
        return;
    }
}
```

**Завантаження даних в ComboBox**
```cpp
void __fastcall TForm1::ComboBox3DblClick(TObject *Sender) {
    AnsiString s;
    ComboBox3->Clear();
    DM2->AT2->First();
    while (!DM2->AT2->Eof) {
        s = DM2->AT2->FieldByName("Код_Клиента")->AsString + " " +
            DM2->AT2->FieldByName("Фио")->AsString;
        ComboBox3->Items->Add(s);
        DM2->AT2->Next();
    }
    ComboBox3->ItemIndex = 0;
}
```

#### Метод Lookup

**Оголошення**:
```cpp
virtual System::Variant __fastcall Lookup(const AnsiString KeyFields, 
                                          const System::Variant &KeyValues, 
                                          const AnsiString ResultFields);
```

**Особливість**: не змінює положення курсору

**Приклад**
```cpp
void __fastcall TForm1::Button20Click(TObject *Sender) {
    float A;
    AnsiString C;
    Variant TText[2];
    Variant LR;
    
    TText[0] = Edit8->Text;
    TText[1] = Edit10->Text;
    
    LR = DM2->AT1->Lookup("Наименование;Тип_Касcеты",
                          VarArrayOf(TText,1), 
                          "Код_Касcеты;Цена");
    
    if (!(VarType(LR) == varNull)) {
        C = LR.GetElement(0);
        A = LR.GetElement(1);
    }
    
    Edit11->Text = "Код_Кассеты=" + C + " " + "Цена=" + FloatToStr(A);
}
```

### 7. Використання компонента ADOQuery

#### Налаштування

1. Додати DataModule з компонентами:
   - ADOConnection
   - ADOQuery
   - DataSource
2. Налаштувати ConnectionString
3. З'єднати DataSource з ADOQuery

#### Простий запит

**В редакторі SQL**:
```sql
Select * from Касети
```

**Програмно**:
```cpp
void __fastcall TForm1::Button2Click(TObject *Sender) {
    DM2->ADOQ1->Close();
    DBGrid1->DataSource = NULL;
    DBN1->DataSource = NULL;
    DBGrid1->DataSource = DM2->DS1;
    DBN1->DataSource = DM2->DS1;
    DM2->ADOQ1->Open();
}
```

#### Динамічний запит з Memo

```cpp
void __fastcall TForm1::Button3Click(TObject *Sender) {
    DM2->ADOQ2->Active = False;
    DBGrid1->DataSource = NULL;
    DBN1->DataSource = NULL;
    DBGrid1->DataSource = DM2->DS2;
    DBN1->DataSource = DM2->DS2;
    
    if (Memo1->Lines->Count > 0) {
        DM2->ADOQ2->SQL = Memo1->Lines;
        DM2->ADOQ2->ExecSQL();
        DM2->ADOQ2->Open();
    }
}
```

#### Запит з умовою LIKE

```cpp
void __fastcall TForm1::Edit1Change(TObject *Sender) {
    DM2->ADOQ2->Close();
    DM2->ADOQ2->SQL->Clear();
    DBGrid1->DataSource = NULL;
    DBN1->DataSource = NULL;
    DBGrid1->DataSource = DM2->DS2;
    DBN1->DataSource = DM2->DS2;
    
    DM2->ADOQ2->SQL->Add("select * from клиент");
    DM2->ADOQ2->SQL->Add("where Фио LIKE '%"+Edit1->Text+"%'");
    DM2->ADOQ2->Open();
}
```

#### Запит зі складними умовами

```cpp
void __fastcall TForm1::Button4Click(TObject *Sender) {
    DM2->ADOQ2->Close();
    DM2->ADOQ2->SQL->Clear();
    DBGrid1->DataSource = DM2->DS2;
    DBN1->DataSource = DM2->DS2;
    
    DM2->ADOQ2->SQL->Add("select * from Пункт_Проката");
    DM2->ADOQ2->SQL->Add("where ((Код_касеты = '004') or (Код_касеты = '003'))");
    DM2->ADOQ2->SQL->Add("and Количество_Копій > 2");
    
    // Інші приклади (закоментовані):
    // DM2->ADOQ2->SQL->Add("where Отметка_возврата = True");
    // DM2->ADOQ2->SQL->Add("where количество_копій > 2");
    // DM2->ADOQ2->SQL->Add("where Дата_Приема > #20/01/2000#");
    // DM2->ADOQ2->SQL->Add("ORDER BY Дата_Выдачи DESC");
    
    DM2->ADOQ2->Open();
}
```

#### Агрегатні функції

**Функції**:
- `AVG` - середнє значення
- `COUNT` - підрахунок кількості
- `MAX` - максимальне значення
- `MIN` - мінімальне значення
- `SUM` - сума значень

**Приклад: максимальна кількість копій**
```cpp
void __fastcall TForm1::Button5Click(TObject *Sender) {
    DM2->ADOQ2->Close();
    DM2->ADOQ2->SQL->Clear();
    DBGrid1->DataSource = DM2->DS2;
    DBN1->DataSource = DM2->DS2;
    
    DM2->ADOQ2->SQL->Add("select Код_касеты,");
    DM2->ADOQ2->SQL->Add("max(Количество_Копій) AS МахКол,");
    DM2->ADOQ2->SQL->Add("count(*) AS Кол from Пункт_Проката");
    DM2->ADOQ2->SQL->Add("GROUP BY Код_касеты");
    DM2->ADOQ2->Open();
}
```

**Приклад з GROUP BY та SUM**:
```sql
Select a.Код_Клиента, b.Піб, sum(Количество_Копій) AS СумКол
From Пункт_Проката a, Клієнт b
where a.Код_Клиента=b.Код_Клиента
GROUP BY a.Код_Клиента, b.ПІБ
```

#### З'єднання таблиць з обчисленням

```cpp
void __fastcall TForm1::Button7Click(TObject *Sender) {
    DM2->ADOQ2->Close();
    DM2->ADOQ2->SQL->Clear();
    DBGrid1->DataSource = DM2->DS2;
    DBN1->DataSource = DM2->DS2;
    
    DM2->ADOQ2->SQL->Add("select v.Код_Касcеты, v.Наименование,");
    DM2->ADOQ2->SQL->Add("v.Цена, w.Количество_копій,");
    DM2->ADOQ2->SQL->Add("w.Количество_копій*v.Цена As Сумма");
    DM2->ADOQ2->SQL->Add("from Пункт_Проката w, Касcеты v");
    DM2->ADOQ2->SQL->Add("where w.Код_кассеты=v.Код_Касcеты");
    DM2->ADOQ2->SQL->Add("ORDER BY v.Код_Касcеты");
    DM2->ADOQ2->Open();
}
```

## Особливості реалізації

### Важливі правила

1. **Зміщення курсору НД** - обов'язково використовувати методи навігації (на відміну від файлів)

2. **Перевірка на NULL** при обчисленнях - для запобігання зависанню програми

3. **Фільтрація**:
   - Оператори відокремлюються пробілами
   - Текстові значення в одинарних лапках
   - Логічні оператори: `and`, `or`, `<>`
   - Дати: `#DD/MM/YYYY#`

4. **Сортування перед фільтрацією** - особливо для часткового пошуку

5. **Відключення зв'язків** перед новим зв'язуванням DBLookupComboBox

6. **GROUP BY** - при використанні агрегатних функцій перераховуються всі поля з SELECT

## Контрольні питання

1. Призначення редактора полів
2. Перерахуйте основні етапи налаштування полів і їх властивостей
3. Для чого призначені поля перегляду? Порядок створення полів перегляду
4. Яка функція попереджає про видалення поточного запису?
5. Які програмні методи використовуються для редагування і додавання запису?
6. Який метод дозволяє вносити зміни полів поточного запису або вставляти нову запис?
7. Як здійснюється настроювання відображення полів таблиці?
8. Настроювання компонента DBLookupComboBox та його основні властивості для забезпечення зв'язку між таблицями
9. Як відбувається зв'язування таблиць за допомогою редактора зв'язку?
10. Перерахувати основні способи доступу до об'єктів полів
11. Перерахувати основні типи та властивості полів
12. Які властивості полів використовуються для визначення імені поля, його розміру і типу?
13. Опишіть процес створення обчислюваного поля
14. Який вигляд має оператор, що виконує сортування?
15. За допомогою яких властивостей включається і відключається фільтрація?
16. Фільтрація полів. Особливості її використання
17. Логічні операції та операції відношення
18. Які методи використовуються для пошуку даних?

## Ліцензія

Навчальний проект для освітніх цілей
