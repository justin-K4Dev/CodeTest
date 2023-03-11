using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;


namespace AdvancedStep
{
    public class ExpressionBodied
    {
        class Point
        {
            public Point(float x, float y)
            {
                m_x = x;
                m_y = y; 
            }

            private float m_x;
			private float m_y;
		}

        class Customer
        {
			// Expression-bodied member : 메서드에서 하나의 Point 객체 리턴
			public Point move(float x, float y) => new Point(X + x, Y + y);

			// Expression-bodied member : 메서드에서 void 리턴
			public void Print() => Console.WriteLine(m_data);

			// Expression-bodied member : 속성에서 get 리턴
			public string Name => FirstName + " " + LastName;

            public string FirstName { get; set; }

            public string LastName { get; set; }

            public float Height { get; set; }

            public float Width { get; set; }

            public float X { get; set; }

            public float Y { get; set; }

			// Expression-bodied member
			public Int32 getId() => m_id;

			// Expression-bodied member : 인덱서에서 Customer 객체 리턴
			public Customer this[Int32 id] => m_customers.FirstOrDefault(x => x.Key == id).Value;


			private Int32 m_id;

            private string m_data;

            private Dictionary<Int32, Customer> m_customers = new Dictionary<int, Customer>();

			// 연산자 메서드 표현
			// 기존의 속성
			public float Area
			{
				get
				{
					return Height * Width;
				}
			}
		}

		public class Complex
		{
			#region 실수 - Real

			/// <summary>
			/// 실수
			/// </summary>
			public double Real { get; set; }

			#endregion
			#region 허수 - Imaginary

			/// <summary>
			/// 허수
			/// </summary>
			public double Imaginary { get; set; }

			#endregion

			#region 생성자 - Complex(real, imaginary)

			/// <summary>
			/// 생성자
			/// </summary>
			/// <param name="real">실수</param>
			/// <param name="imaginary">허수</param>
			public Complex(double real, double imaginary)
			{
				Real = real;
				Imaginary = imaginary;
			}

			#endregion

			#region 연산자 + 재정의하기 - operator +(a, b)

			/// <summary>
			/// 연산자 + 재정의하기 : Expression-bodied member
			/// </summary>
			/// <param name="a">복소수 A</param>
			/// <param name="b">복소수 B</param>
			/// <returns>복소수</returns>
			public static Complex operator +(Complex a, Complex b) => new Complex(a.Real + b.Real, a.Imaginary + b.Imaginary);

			#endregion
		}

		public static void Test()
        {
            // Expression-bodied member 사용
            {
                /*
                    C#의 속성이나 메서드는 보통 여러 문장(statement)들로 구성된 블럭을 실행하게 된다.
                    하지만 속성이나 메서드의 Body 블럭이 간단한 경우,
                    Statement Block을 사용하는 대신 간단한 함수식(expression)을 사용할 수 있는데,
                    이를 Expression-bodied member 표현이라 한다.
                    이는 기존의 람다식과 유사한 것으로 속성이나 메서드 Body를 간략한 람다식처럼 표현한 것이다.
                    예를 들어, 아래 예제에서 처럼 기존에는 Area 속성의 get 블럭안에 리턴 식을 표현했지만,
                    C# 6.0에서는 이를 간략하게 람다 화살표로 표현하고 있다.               
                */
                {
                }
            }

            // 다양한 Expression-bodied member 표현
            {
                /*
                    메서드에서 Expression-bodied member를 사용하면 하나의 리턴 값을 가질 수 있고 혹은 void 리턴을 할 수도 있다.
                    속성에서 사용하는 Expression-bodied member는 getter로서 하나의 값을 리턴한다.
                    메서드나 속성 이외에도 인덱서, Operator 연산자 등에서 Expression-bodied member 표현을 사용할 수 있다.
                    아래 예제들은 이러한 다양한 종류의 Expression-bodied member 표현 예들이다.
                */
                {
                }
            }
        }
    }
}
