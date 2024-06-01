//
// Created by ianpo on 01/06/2024.
//

#pragma once

#include <memory>

namespace Core {

   //TODO: Make my own smart pointers.

   template<typename T>
   using Scope = std::unique_ptr<T>;
   template<typename T, typename ... Args>
   constexpr Scope<T> CreateScope(Args&& ... args)
   {
      return std::make_unique<T>(std::forward<Args>(args)...);
   }

   template<typename T>
   using Ref = std::shared_ptr<T>;
   template<typename T, typename ... Args>
   constexpr Ref<T> CreateRef(Args&& ... args)
   {
      return std::make_shared<T>(std::forward<Args>(args)...);
   }

   template<typename T>
   using Weak = std::weak_ptr<T>;

   template<typename TTarget, typename TBasePtr>
   [[nodiscard]] inline Ref<TTarget> CastPtr(TBasePtr ptr)
   {
      return std::static_pointer_cast<TTarget>(ptr);
   }

} // Core
